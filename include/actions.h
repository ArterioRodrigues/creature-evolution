#pragma once
#include "creature.h"
#include "world.h"

void executeActions(Creature &self, World &world, const std::unordered_map<Neuron::Type, float> &actionLevels,
                    int currentStep);
