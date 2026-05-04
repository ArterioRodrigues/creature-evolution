#include "simulation.h"
#include "configuration.h"
#include "selection.h"

Simulation::Simulation() : _currentGeneration(0), _currentStep(0), _world() {}

void Simulation::runOneStep() {
  for (auto &creature : _world.getCreatures()) {
    creature.stepOnce(_world, _currentStep);
  }
  _currentStep++;
  _world.getSignal().decay();
}

void Simulation::runOneGeneration() {
  while (_currentStep < Configuration::steps) runOneStep();
}

void Simulation::endOfGeneration() {
  int survivorCount = _world.repopulate();
  _currentGeneration++;
  _currentStep = 0;

  while (survivorCount == -1) {
    std::cout << "END OF SIMULATION" << std::endl;
  }

  static std::ofstream log("media/logs/epoch.txt", std::ios::app);
  log << _currentGeneration << "," << Configuration::population << "," << survivorCount << ","
      << float(float(survivorCount) / Configuration::population) << std::endl;
}

int Simulation::getCurrentGeneration() const { return _currentGeneration; }
int Simulation::getCurrentStep() const { return _currentStep; }
World &Simulation::getWorld() { return _world; }
