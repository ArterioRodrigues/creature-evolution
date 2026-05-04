#pragma once
#include "pch.h"

class Signal : public sf::Drawable {
public:
  Signal(int width, int height);

  void emit(int x, int y, int radius, uint8_t amount);
  int16_t at(int x, int y) const;

  void set(int x, int y, uint8_t value);
  int getWidth() const;
  int getHeight() const;

  void clear();
  void decay();

private:
  std::vector<std::vector<uint8_t>> _cells;
  int _width;
  int _height;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
