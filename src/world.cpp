#include "world.h"
#include "configuration.h"
#include "creature.h"
#include "helper.h"

World::World() : _grid(Configuration::gridWidth, Configuration::gridHeight) {
  for (int i = 0; i < Configuration::population; i++) {
    int x = randomNumberGenerator(0, Configuration::gridWidth - 1);
    int y = randomNumberGenerator(0, Configuration::gridHeight - 1);

    while (!_grid.isEmptyAt(x, y)) {
      x = randomNumberGenerator(0, Configuration::gridWidth - 1);
      y = randomNumberGenerator(0, Configuration::gridHeight - 1);
    }

    _grid.set(x, y, i + 1);

    Creature creature(8);
    creature.setLocation(x, y);
    creatures.push_back(creature);
  }
}
const std::vector<Creature> &World::getCreatures() { return creatures; }

Grid& World::getGrid() {
  return _grid;
}
