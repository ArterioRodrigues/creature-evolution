#include "simulation.h"
#include "configuration.h"
#include "selection.h"

Simulation::Simulation() : _currentGeneration(0), _currentStep(0), _world() {}

void Simulation::runOneStep() {
  for (auto &creature : _world.getCreatures()) {
    creature.stepOnce(_world, _currentStep);
  }
  _currentStep++;
}

void Simulation::runOneGeneration() {
  while (_currentStep < Configuration::steps) runOneStep();
}

void Simulation::endOfGeneration() {
  _world.repopulate();
  _currentGeneration++;
  _currentStep = 0;
}

int Simulation::getCurrentGeneration() const { return _currentGeneration; }
int Simulation::getCurrentStep() const { return _currentStep; }
World &Simulation::getWorld() { return _world; }
