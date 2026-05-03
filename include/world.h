#pragma once
#include "creature.h"
#include "grid.h"
#include "pch.h"

class World {
public:
  World();
  std::vector<Creature> &getCreatures();

  Grid& getGrid();

private:
  std::vector<Creature> creatures;
  Grid _grid; 
};
