#include "simulation.h"
#include "configuration.h"

Simulation::Simulation() : _currentGeneration(0), _currentStep(0), _world() {}

void Simulation::runOneStep() {
  for (auto& creature : _world.getCreatures()) {
    creature.stepOnce(_world, _currentStep);
  }
  _currentStep++;
}

void Simulation::runOneGeneration() {
  while (_currentStep < Configuration::steps) runOneStep();
}

void Simulation::endOfGeneration() {}
