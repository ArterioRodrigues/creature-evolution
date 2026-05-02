#pragma once
#include "creature.h"
#include "neuron.h"
#include "world.h"

float computeSensor(Neuron::Type sensorType, const Creature &self, const World &world, int currentStep);
