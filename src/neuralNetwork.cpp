#include "neuralNetwork.h"
#include <cstdint>

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
}

const std::vector<NeuronConnection> &NeuralNetwork::getConnections() const { return _connections; }
