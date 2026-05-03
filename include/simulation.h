#pragma once
#include "world.h"

class Simulation {
public:
  Simulation();

  void runOneStep();
  void runOneGeneration();
  void endOfGeneration();

  int getCurrentGeneration() const;
  int getCurrentStep() const;
  World &getWorld();

private:
  World _world;

  int _currentGeneration;
  int _currentStep;
};
