#pragma once
#include "genome.h"
#include "neuron.h"
#include "pch.h"

struct NeuronConnection {
  Neuron::Type sourceType;
  int sourceId;
  Neuron::Type sinkType;
  int sinkId;
  float weight;
};

class NeuralNetwork {
public:
  NeuralNetwork(Genome genome, int internalNeuronCount = 3);

  const std::vector<NeuronConnection> &getConnections() const;

private:
  std::vector<NeuronConnection> _connections;
};
