#pragma once
#include "pch.h"

enum class Compass { N, NE, E, SE, S, SW, W, NW, CENTER };
std::pair<int, int> compassToDelta(Compass d);
Compass deltaToCompass(int x, int y);

Compass rotateRight(Compass c);
Compass rotateLeft(Compass c);
