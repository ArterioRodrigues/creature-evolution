#include "selection.h"
#include "configuration.h"
#include "creature.h"

bool survives(const Creature &c, const World &world) { return c.getX() > Configuration::gridWidth / 2; }
