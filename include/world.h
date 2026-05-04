#pragma once
#include "creature.h"
#include "grid.h"
#include "pch.h"

class World {
public:
  World();
  std::vector<Creature> &getCreatures();

  void repopulate();
  Grid& getGrid();

private:
  std::vector<Creature> _creatures;
  Grid _grid; 
};
