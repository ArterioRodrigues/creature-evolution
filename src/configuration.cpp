#include "configuration.h"

bool Configuration::enableKill = false;
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

BarrierType Configuration::barrier = BarrierType::None;
SelectionType Configuration::selection = SelectionType::RightHalf;

Configuration::Configuration() {
  windowX = 1000;
  windowY = 800;

  frameRate = 30;
  mutation = 0.005;

  steps = 300;
  fastFowardCount = 10000;

  decayRate = 1;
  neurons = 4;
  population = 1000;
  genomeLength = 32;

  gridWidth = 128;
  gridHeight = 128;

  enableKill = true;
  barrier = BarrierType::None;
  selection = SelectionType::CenterCircle;
}
