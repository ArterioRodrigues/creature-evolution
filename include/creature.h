#pragma once
#include "compass.h"
#include "genome.h"
#include "neuralNetwork.h"
#include "pch.h"

class Creature : public sf::Drawable {
public:
  Creature(int genomeLenght);
  Creature(const std::string &parentGenome, float mutationRate);

  int getX() const;
  int getY() const;

  void setLocation(int x, int y);

  Compass getLastMoveDir() const;
  Genome getGenome() const;
  void setLastMoveDir(Compass d);
  void stepOnce(World &world, int currentStep);
  bool isAlive() const;
  void setAlive(bool a);
  int getLongProbeDistance() const;
  void setLongProbeDistance(int d);

  float getOscillatorPeriod() const;
  void setOscillatorPeriod(float p);

  float getResponsiveness() const;
  void setResponsiveness(float r);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

  int _x;
  int _y;
  bool _alive;
  sf::CircleShape _circle;
  Genome _genome;
  NeuralNetwork _brain;
  Compass _lastMoveDir;
  int _longProbeDistance;
  float _oscillatorPeriod;
  float _responsiveness;
};
