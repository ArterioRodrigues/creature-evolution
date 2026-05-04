#include "neuralNetwork.h"
#include "sensors.h"

NeuralNetwork::NeuralNetwork(Genome genome, int internalNeuronCount) {
  for (auto gen : genome.getGens()) {
    NeuronConnection conn;

    // 1. Source type bit: '0' -> SENSORY, '1' -> INTERNAL
    conn.sourceType = (gen.sourceType == '0') ? Neuron::Type::SENSORY : Neuron::Type::INTERNAL;

    // 2. Sink type bit: '0' -> INTERNAL, '1' -> ACTION
    conn.sinkType = (gen.sinkType == '0') ? Neuron::Type::INTERNAL : Neuron::Type::ACTION;

    // 3. Source ID
    int rawSourceId = std::stoi(gen.sourceId, nullptr, 2);
    if (conn.sourceType == Neuron::Type::SENSORY) {
      // Map 0..SENSORY_TYPE_SIZE-1 onto the sensor block of the enum.
      // Using the enum value of Slr keeps this correct if the enum is reordered.
      conn.sourceId = static_cast<int>(Neuron::Type::Slr) + (rawSourceId % SENSORY_TYPE_SIZE);
    } else {
      // INTERNAL: raw index 0..N-1
      conn.sourceId = rawSourceId % internalNeuronCount;
    }

    // 4. Sink ID
    int rawSinkId = std::stoi(gen.sinkId, nullptr, 2);
    if (conn.sinkType == Neuron::Type::ACTION) {
      // Map 0..ACTION_TYPE_SIZE-1 onto the action block of the enum.
      conn.sinkId = static_cast<int>(Neuron::Type::LPD) + (rawSinkId % ACTION_TYPE_SIZE);
    } else {
      // INTERNAL: raw index 0..N-1
      conn.sinkId = rawSinkId % internalNeuronCount;
    }

    // 5. Weight: 16 bits reinterpreted as signed int16, scaled to ~[-4.1, 4.1]
    uint16_t raw = static_cast<uint16_t>(std::stoi(gen.weight, nullptr, 2));
    int16_t signedRaw = static_cast<int16_t>(raw);
    conn.weight = signedRaw / 8000.0f;

    _connections.push_back(conn);
  }
  prune();
  _internalState.assign(_internalCount, 0.0f);
}

const std::vector<NeuronConnection> &NeuralNetwork::getConnections() const { return _connections; }

void NeuralNetwork::prune() {
  std::set<int> liveInternals;
  for (const auto &c : _connections) {
    if (c.sourceType == Neuron::Type::INTERNAL) liveInternals.insert(c.sourceId);
    if (c.sinkType == Neuron::Type::INTERNAL) liveInternals.insert(c.sinkId);
  }

  bool changed = true;
  while (changed) {
    changed = false;
    std::set<int> toRemove;

    for (int id : liveInternals) {
      bool hasInput = false;
      bool hasOutput = false;

      for (const auto &c : _connections) {
        if (c.sinkType == Neuron::Type::INTERNAL && c.sinkId == id) {
          bool isSelfLoop = (c.sourceType == Neuron::Type::INTERNAL && c.sourceId == id);
          if (!isSelfLoop) hasInput = true;
        }
        if (c.sourceType == Neuron::Type::INTERNAL && c.sourceId == id) hasOutput = true;

        if (hasInput && hasOutput) break;
      }

      if (!hasInput || !hasOutput) toRemove.insert(id);
    }

    if (toRemove.empty()) continue;
    changed = true;

    _connections.erase(std::remove_if(_connections.begin(), _connections.end(),
                                      [&](const NeuronConnection &c) {
                                        if (c.sourceType == Neuron::Type::INTERNAL && toRemove.count(c.sourceId))
                                          return true;
                                        if (c.sinkType == Neuron::Type::INTERNAL && toRemove.count(c.sinkId))
                                          return true;
                                        return false;
                                      }),
                       _connections.end());

    for (int id : toRemove) liveInternals.erase(id);
  }

  std::unordered_map<int, int> remap;
  int dense = 0;
  for (int oldId : liveInternals) remap[oldId] = dense++;
  _internalCount = dense;

  for (auto &c : _connections) {
    if (c.sourceType == Neuron::Type::INTERNAL) c.sourceId = remap[c.sourceId];
    if (c.sinkType == Neuron::Type::INTERNAL) c.sinkId = remap[c.sinkId];
  }
}

std::unordered_map<Neuron::Type, float> NeuralNetwork::feedForward(const Creature &self, World &world,
                                                                   int currentStep) {
  // 1. Cache each used sensor exactly once.
  std::unordered_map<int, float> sensorCache;
  for (const auto &c : _connections) {
    if (c.sourceType == Neuron::Type::SENSORY && sensorCache.find(c.sourceId) == sensorCache.end()) {
      sensorCache[c.sourceId] = computeSensor(static_cast<Neuron::Type>(c.sourceId), self, world, currentStep);
    }
  }

  // 2. Accumulators.
  std::vector<float> internalAccum(_internalCount, 0.0f);
  std::unordered_map<Neuron::Type, float> actionAccum;

  // 3. First pass: feed INTERNAL sinks. Internal-to-internal reads use the
  //    PREVIOUS step's state, so self-loops and recurrent cycles work.
  for (const auto &c : _connections) {
    if (c.sinkType != Neuron::Type::INTERNAL) continue;

    float sourceVal = (c.sourceType == Neuron::Type::SENSORY) ? sensorCache[c.sourceId] : _internalState[c.sourceId];
    internalAccum[c.sinkId] += sourceVal * c.weight;
  }

  // 4. tanh into the new internal state.
  std::vector<float> newInternalState(_internalCount);
  for (int i = 0; i < _internalCount; ++i) {
    newInternalState[i] = std::tanh(internalAccum[i]);
  }

  // 5. Second pass: feed ACTION sinks using THIS step's just-computed state,
  //    so motor outputs aren't a tick stale.
  for (const auto &c : _connections) {
    if (c.sinkType != Neuron::Type::ACTION) continue;

    float sourceVal = (c.sourceType == Neuron::Type::SENSORY) ? sensorCache[c.sourceId] : newInternalState[c.sourceId];
    actionAccum[static_cast<Neuron::Type>(c.sinkId)] += sourceVal * c.weight;
  }

  // 6. tanh on actions, build result.
  std::unordered_map<Neuron::Type, float> actionLevels;
  for (const auto &[type, sum] : actionAccum) {
    actionLevels[type] = std::tanh(sum);
  }
  _internalState = std::move(newInternalState);

  return actionLevels;
}
