#include "configuration.h"

unsigned int Configuration::windowX = 0;
unsigned int Configuration::windowY = 0;

unsigned int Configuration::steps = 0;
unsigned int Configuration::neurons = 0;
unsigned int Configuration::population = 0;
unsigned int Configuration::genomeLength = 0;
unsigned int Configuration::fastFowardCount = 0;

int Configuration::gridWidth = 0;
int Configuration::gridHeight = 0;

float Configuration::mutation = 0;
float Configuration::decayRate = 0;
double Configuration::frameRate = 0;

Configuration::Configuration() {
  windowX = 1000;
  windowY = 800;

  frameRate = 30;
  mutation = 0.01;

  steps = 500;
  fastFowardCount = 1000;

  decayRate = 1;
  neurons = 12;
  population = 50;
  genomeLength = 32;

  gridWidth = 128;
  gridHeight = 128;
}
