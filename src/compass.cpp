#include "compass.h"

std::pair<int, int> compassToDelta(Compass d) {
  switch (d) {
  case Compass::N:
    return {0, -1};
    break;
  case Compass::NE:
    return {1, -1};
    break;
  case Compass::E:
    return {1, 0};
    break;
  case Compass::SE:
    return {1, 1};
    break;
  case Compass::S:
    return {0, 1};
    break;
  case Compass::SW:
    return {-1, 1};
    break;
  case Compass::W:
    return {-1, 0};
    break;
  case Compass::NW:
    return {-1, -1};
    break;
  case Compass::CENTER:
    return {0, 0};
    break;
  }

  return {0, 0};
}

Compass rotateRight(Compass c) { return static_cast<Compass>((static_cast<int>(c) + 1) % 8); }
Compass rotateLeft(Compass c) {
  return static_cast<Compass>((static_cast<int>(c) + 7) % 8); // -1 mod 8
}

Compass deltaToCompass(int x, int y) {
  if (x == 0 && y == -1)
    return Compass::N;
  else if (x == 1 && y == -1)
    return Compass::NE;
  else if (x == 1 && y == 0)
    return Compass::E;
  else if (x == 1 && y == 1)
    return Compass::SE;
  else if (x == 0 && y == 1)
    return Compass::S;
  else if (x == -1 && y == 1)
    return Compass::SW;
  else if (x == -1 && y == 0)
    return Compass::W;
  else if (x == -1 && y == -1)
    return Compass::NW;
  else
    return Compass::CENTER;
}
