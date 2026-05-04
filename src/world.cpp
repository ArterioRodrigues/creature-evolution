#include "world.h"
#include "configuration.h"
#include "creature.h"
#include "helper.h"
#include "selection.h"

World::World()
    : _grid(Configuration::gridWidth, Configuration::gridHeight),
      _signal(Configuration::gridWidth, Configuration::gridHeight) {
  for (int i = 0; i < Configuration::population; i++) {
    int x = randomNumberGenerator(0, Configuration::gridWidth - 1);
    int y = randomNumberGenerator(0, Configuration::gridHeight - 1);

    while (!_grid.isEmptyAt(x, y)) {
      x = randomNumberGenerator(0, Configuration::gridWidth - 1);
      y = randomNumberGenerator(0, Configuration::gridHeight - 1);
    }

    _grid.set(x, y, i + 1);

    Creature creature(Configuration::genomeLength);
    creature.setLocation(x, y);
    _creatures.push_back(creature);
  }
}

std::vector<Creature> &World::getCreatures() { return _creatures; }

Grid &World::getGrid() { return _grid; }
Signal &World::getSignal() { return _signal; }
Selection &World::getSelection() { return _selection; }

int World::repopulate() {
  std::vector<Creature> aliveCreature;

  for (auto &creature : _creatures) {
    bool alive = _selection.survives(creature, *this);

    creature.setAlive(alive);
    if (!alive) continue;

    aliveCreature.push_back(creature);
  }

  _grid.clear();
  _signal.clear();
  _creatures.clear();

  if (aliveCreature.size() == 0) {
    return -1;
  };

  for (int i = 0; i < Configuration::population; i++) {
    int x = randomNumberGenerator(0, Configuration::gridWidth - 1);
    int y = randomNumberGenerator(0, Configuration::gridHeight - 1);

    while (!_grid.isEmptyAt(x, y)) {
      x = randomNumberGenerator(0, Configuration::gridWidth - 1);
      y = randomNumberGenerator(0, Configuration::gridHeight - 1);
    }

    _grid.set(x, y, i + 1);

    Creature creature(aliveCreature[randomNumberGenerator(0, aliveCreature.size() - 1)].getGenome().toString(),
                      Configuration::mutation);
    creature.setLocation(x, y);
    _creatures.push_back(creature);
  }

  return aliveCreature.size();
}

