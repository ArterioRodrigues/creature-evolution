#pragma once
#include "genome.h"
#include "neuron.h"
#include "pch.h"

class Creature;
class World;

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
  std::unordered_map<Neuron::Type, float> feedForward(const Creature &self, const World &world, int currentStep);
  int getInternalCount() const { return _internalCount; }

private:
  void prune();
  float computeSensor(int sensorId, const Creature &self, const World &world, int currentStep) const;
  int _internalCount;
  std::vector<NeuronConnection> _connections;
  std::vector<float> _internalState;
};
