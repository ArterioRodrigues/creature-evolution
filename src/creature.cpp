#include "creature.h"
#include "configuration.h"
#include "helper.h"

Creature::Creature(int genomeLenght) : _genome(genomeLenght), _brain(_genome) {
  uint8_t red = randomNumberGenerator(0, 255);
  uint8_t green = randomNumberGenerator(0, 255);
  uint8_t blue = randomNumberGenerator(0, 255);

  _x = 0;
  _y = 0;

  _circle.setRadius(2);
  _circle.setFillColor({red, green, blue});

  _lastMoveDir = Compass(randomNumberGenerator(0, 7));
}

void Creature::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  float pixelX = _x * (float(Configuration::windowX) / Configuration::gridWidth);
  float pixelY = _y * (float(Configuration::windowY) / Configuration::gridHeight);

  sf::CircleShape c = _circle;
  c.setPosition({pixelX, pixelY});
  target.draw(c, states);
}

void Creature::setLocation(int x, int y) {
  _x = x;
  _y = y;
}

int Creature::getX() const { return _x; }
int Creature::getY() const { return _y; }
Compass Creature::getLastMoveDir() const { return _lastMoveDir; }
void Creature::setLastMoveDir(Compass d) { _lastMoveDir = d; }
