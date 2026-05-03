#pragma once
#include "compass.h"
#include "genome.h"
#include "neuralNetwork.h"
#include "pch.h"

class Creature : public sf::Drawable {
public:
  Creature(int genomeLenght);

  int getX() const;
  int getY() const;

  void setLocation(int x, int y);

  Compass getLastMoveDir() const;
  void setLastMoveDir(Compass d);
  void stepOnce(World &world, int currentStep);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

  int _x;
  int _y;
  bool _alive;
  sf::CircleShape _circle;
  Genome _genome;
  NeuralNetwork _brain;
  Compass _lastMoveDir;
};
