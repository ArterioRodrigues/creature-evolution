#pragma once
#include "pch.h"

class Configuration {
public:
  static unsigned int windowX;
  static unsigned int windowY;

  static unsigned int fastFowardCount;
  static unsigned int steps;
  static unsigned int neurons;
  static unsigned int population;
  static unsigned int genomeLength;

  static int gridWidth;
  static int gridHeight;

  static float mutation;
  static float decayRate;

  static double frameRate;

  Configuration();
};
