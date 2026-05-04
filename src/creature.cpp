#include "creature.h"
#include "actions.h"
#include "configuration.h"
#include "helper.h"

namespace {
sf::Color colorFromGenome(const std::string &hex) {
  uint8_t red = (hexToDecimal(hex[0]) << 4) | hexToDecimal(hex[1]);
  uint8_t green = (hexToDecimal(hex[2]) << 4) | hexToDecimal(hex[3]);
  uint8_t blue = (hexToDecimal(hex[4]) << 4) | hexToDecimal(hex[5]);
  return sf::Color(red, green, blue);
}
} // namespace

Creature::Creature(int genomeLenght) : _genome(genomeLenght), _brain(_genome) {
  _x = 0;
  _y = 0;

  _circle.setRadius(2);
  _circle.setFillColor(colorFromGenome(_genome.toString()));

  _lastMoveDir = Compass(randomNumberGenerator(0, 7));
  _alive = true;

  _longProbeDistance = 16;
  _oscillatorPeriod = 34.0f;
  _responsiveness = 1.0f;
}

Creature::Creature(const std::string &parentGenome, float mutationRate)
    : _genome(parentGenome, mutationRate), _brain(_genome) {
  _x = 0;
  _y = 0;

  _circle.setRadius(2);
  _circle.setFillColor(colorFromGenome(_genome.toString()));

  _lastMoveDir = Compass(randomNumberGenerator(0, 7));
  _alive = true;

  _longProbeDistance = 16;
  _oscillatorPeriod = 34.0f;
  _responsiveness = 1.0f;
}

void Creature::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  float pixelX = _x * (float(Configuration::windowX) / Configuration::gridWidth);
  float pixelY = _y * (float(Configuration::windowY) / Configuration::gridHeight);

  sf::CircleShape c = _circle;
  if (!_alive) c.setFillColor(sf::Color(80, 80, 80));
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
Genome Creature::getGenome() const { return _genome; }

void Creature::setLastMoveDir(Compass d) { _lastMoveDir = d; }
void Creature::stepOnce(World &world, int currentStep) {
  if (!_alive) return;

  auto actionLevels = _brain.feedForward(*this, world, currentStep);
  executeActions(*this, world, actionLevels, currentStep);
}

bool Creature::isAlive() const { return _alive; }
void Creature::setAlive(bool a) { _alive = a; }

int Creature::getLongProbeDistance() const { return _longProbeDistance; }
void Creature::setLongProbeDistance(int d) { _longProbeDistance = std::clamp(d, 1, 32); }

float Creature::getOscillatorPeriod() const { return _oscillatorPeriod; }
void Creature::setOscillatorPeriod(float p) { _oscillatorPeriod = std::clamp(p, 2.0f, 256.0f); }

float Creature::getResponsiveness() const { return _responsiveness; }
void Creature::setResponsiveness(float r) { _responsiveness = std::clamp(r, 0.0f, 1.0f); }
