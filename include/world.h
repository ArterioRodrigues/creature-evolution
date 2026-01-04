#pragma once
#include "creature.h"
#include "pch.h"

class World {
public:
  World();
  const std::vector<Creature> &getCreatures();

private:
  std::vector<Creature> creatures;
};
