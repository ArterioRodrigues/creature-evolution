#include "creature.h"
#include "configuration.h"
#include "helper.h"
#include <cstdint>

Creature::Creature(int genomeLenght): _genome(genomeLenght), _brain(_genome) {
  uint8_t red = randomNumberGenerator(0, 255);
  uint8_t green = randomNumberGenerator(0, 255);
  uint8_t blue = randomNumberGenerator(0, 255);

  _position = sf::Vector2f(randomNumberGenerator(0, Configuration::windowX),
                           randomNumberGenerator(0, Configuration::windowY));
   
  _circle.setRadius(2);
  _circle.setPosition(_position);
  _circle.setFillColor({red, green, blue});
}

void Creature::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(_circle, states);
}
