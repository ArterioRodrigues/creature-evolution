#pragma once
#include "pch.h"

class Creature : public sf::Drawable {
public:
  Creature();

private:
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;

  sf::CircleShape _circle;
  sf::Vector2f _position;
};
