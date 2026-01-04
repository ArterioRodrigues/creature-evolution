#pragma once
#include "configuration.h"
#include "pch.h"

class Game {
public:
  Game();

  void run(int frameRate = Configuration::frameRate);
  void processEvents();
  void update(sf::Time deltaTime);
  void render();

private:
  sf::RenderWindow _window;
  int _x;
  int _y;
};
