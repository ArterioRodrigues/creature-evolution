#pragma once

#include "pch.h"
class Creature;
class World;

class Selection : public sf::Drawable {
public:
  bool survives(const Creature &c, const World &world);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
