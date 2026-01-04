#include "configuration.h"

ResourceManager<sf::Texture, int> Configuration::textures;
unsigned int Configuration::windowX = 0;
unsigned int Configuration::windowY = 0;

unsigned int Configuration::steps = 0;
unsigned int Configuration::neurons = 0;
unsigned int Configuration::population = 0;
unsigned int Configuration::genomeLength = 0;

float Configuration::mutation = 0;
double Configuration::frameRate = 0;

World* Configuration::world = nullptr;
Configuration::Configuration() {
  windowX = 1000;
  windowY = 800;
  frameRate = 30;
  mutation = 0.01;

  population = 1000;
  steps = 300;
  genomeLength = 4;
  neurons = 1;
  
  world = new World();
}
