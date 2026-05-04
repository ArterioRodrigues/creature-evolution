#pragma once
#include "creature.h"
#include "neuron.h"
#include "world.h"

float computeSensor(Neuron::Type sensorType, const Creature &self, World &world, int currentStep);
