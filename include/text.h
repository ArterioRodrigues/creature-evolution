#pragma once
#include "pch.h"

class Text: public sf::Drawable {
public:
  Text(std::string content);
  Text(std::string content, float x, float y);
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
private:
  sf::Text _text;
  sf::Font _font;
};
