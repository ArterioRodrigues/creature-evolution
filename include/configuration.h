#pragma once
#include "pch.h"

enum BarrierType {None, HorizontalBar, VeriticalBar};
enum class SelectionType {
  RightHalf,         
  LeftHalf,         
  CenterSquare,    
  CenterCircle,   
  Corners,       
  HorizontalBand,
  VerticalBand,  
  EastWestEdges,
};
 
class Configuration {
public:
  static bool enableKill;
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
  static SelectionType selection;
  static BarrierType barrier;
  Configuration();
};
