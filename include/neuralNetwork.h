#include "neuron.h"

struct NeuronConnection {
  Neuron *from;
  Neuron *to;
  float weight;
};

class NeuralNetowrk {
public:
  NeuralNetowrk(Genome genome, int internalNeuronCount = 3) {
    for (auto gen : genome.getGens()) {
      NeuronConnection *connection = new NeuronConnection;

      Neuron::Type sourceType = Neuron::Type(int(gen.sourceType - '0'));
      Neuron::Type sinkType = Neuron::Type(int(gen.sinkType - '0') + 1);

      int sourceId = std::stoi(gen.sourceId, nullptr, 2);
      int sinkId = std::stoi(gen.sinkId, nullptr, 2);
      connection->from = new Neuron(sourceType, sourceId, internalNeuronCount);
      connection->to = new Neuron(sinkType, sinkId, internalNeuronCount);
      connection->weight = float(stoi(gen.weight, nullptr, 2)) / 8000 - 4;

      _connections.push_back(*connection);
    }
  }
  

private:
  std::vector<NeuronConnection> _connections;
};
