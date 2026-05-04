#include "configuration.h"

unsigned int Configuration::windowX = 0;
unsigned int Configuration::windowY = 0;

unsigned int Configuration::steps = 0;
unsigned int Configuration::neurons = 0;
unsigned int Configuration::population = 0;
unsigned int Configuration::genomeLength = 0;

int Configuration::gridWidth = 0;
int Configuration::gridHeight = 0;

float Configuration::mutation = 0;
double Configuration::frameRate = 0;

Configuration::Configuration() {
  windowX = 1000;
  windowY = 800;

  frameRate = 30;
  mutation = 0.01;

  steps = 300;
  neurons = 1;
  population = 50;
  genomeLength = 4;

  gridWidth = 128;
  gridHeight = 128;
}
