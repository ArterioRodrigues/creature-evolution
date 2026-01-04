#include "world.h"
#include "configuration.h"
#include "creature.h"

World::World() {
  for (int i = 0; i < Configuration::population; i++) {
    Creature *creature = new Creature();
    creatures.push_back(*creature);
  }
}
const std::vector<Creature> &World::getCreatures() { return creatures; }
