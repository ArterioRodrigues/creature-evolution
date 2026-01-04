#pragma once
#include "pch.h"
#include "resourceManager.h"
#include "world.h"

class Configuration {
public:
  enum Textures : int {
    Player,
  };
  static ResourceManager<sf::Texture, int> textures;

  static unsigned int windowX;
  static unsigned int windowY;

  static unsigned int steps;
  static unsigned int neurons;
  static unsigned int population;
  static unsigned int genomeLength;

  static float mutation;

  static double frameRate;
  static World* world;
  Configuration();
};
