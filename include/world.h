#pragma once
#include "creature.h"
#include "selection.h"
#include "grid.h"
#include "signal.h"
#include "pch.h"

class World {
public:
  World();
  std::vector<Creature> &getCreatures();

  int repopulate();
  Grid& getGrid();
  Signal& getSignal();
  Selection& getSelection();

private:
  std::vector<Creature> _creatures;
  Grid _grid; 
  Signal _signal;
  Selection _selection;

};
