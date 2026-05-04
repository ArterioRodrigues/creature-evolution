#include "selection.h"
#include "configuration.h"
#include "creature.h"

bool Selection::survives(const Creature &c, const World &world) { return c.getX() > Configuration::gridWidth / 2; }
void Selection::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::RectangleShape rect;
  rect.setSize({Configuration::windowX / 2.0f, (float)Configuration::windowY});
  rect.setPosition({Configuration::windowX / 2.0f, 0.0f});
  rect.setFillColor(sf::Color(0, 255, 0, 50));
  target.draw(rect, states);
}
