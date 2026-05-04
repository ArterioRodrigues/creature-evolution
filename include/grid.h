#pragma once
#include "pch.h"

class Grid : public sf::Drawable {
public:
  Grid(int width, int height);
  bool isInBounds(int x, int y) const;
  bool isEmptyAt(int x, int y) const;
  bool isOccupiedAt(int x, int y) const;
  int16_t at(int x, int y) const;

  bool isBarrierAt(int x, int y);
  void setBarrier(int x, int y);
  void set(int x, int y, int16_t value);
  void move(int fromX, int fromY, int toX, int toY);
  int getWidth() const;
  int getHeight() const;

  void clear();

private:
  std::vector<std::vector<int16_t>> _cells;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  int _width;
  int _height;
};
