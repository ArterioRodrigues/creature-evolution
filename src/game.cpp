#include "game.h"
#include "simulation.h"
#include "configuration.h"
#include "creature.h"

Game::Game() : _window(sf::VideoMode({Configuration::windowX, Configuration::windowY}), "Evolution Simultaion") {
  _x = Configuration::windowX;
  _y = Configuration::windowY;
}

void Game::run(int frameRate) {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time timePerFrame = sf::seconds(1.f / frameRate);
  while (_window.isOpen()) {
    processEvents();
    timeSinceLastUpdate += clock.restart();

    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      update(timePerFrame);
    }
    render();
  }
}

void Game::processEvents() {
  std::optional<sf::Event> optionalEvent = _window.pollEvent();
  while (optionalEvent.has_value()) {
    sf::Event event = optionalEvent.value();

    if (event.is<sf::Event::Closed>()) {
      _window.close();
    }

    else if (event.is<sf::Event::KeyPressed>()) {
      sf::Keyboard::Key code = event.getIf<sf::Event::KeyPressed>()->code;

      if (code == sf::Keyboard::Key::Escape) {
        _window.close();
      }
    }
    optionalEvent = _window.pollEvent();
  }
}

void Game::update(sf::Time deltaTime) {
  _simulation.runOneStep();

  if (_simulation.getCurrentStep() >= Configuration::steps) _simulation.endOfGeneration();
}

void Game::render() {
  _window.clear(sf::Color::White);
  for (Creature creature : _simulation.getWorld().getCreatures()) {
    _window.draw(creature);
  }
  _window.display();
}
