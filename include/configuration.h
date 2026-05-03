#pragma once
#include "pch.h"
#include "world.h"

class Configuration {
public:
  static unsigned int windowX;
  static unsigned int windowY;

  static unsigned int steps;
  static unsigned int neurons;
  static unsigned int population;
  static unsigned int genomeLength;

  static int gridWidth;
  static int gridHeight;

  static float mutation;

  static double frameRate;

  Configuration();
};
