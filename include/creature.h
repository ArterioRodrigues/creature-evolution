#pragma once
#include "genome.h"
#include "neuralNetwork.h"
#include "pch.h"

class Creature : public sf::Drawable {
public:
  Creature(int genomeLenght);

private:
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;

  sf::CircleShape _circle;
  sf::Vector2f _position;
  Genome _genome;
  NeuralNetowrk _brain;
};
