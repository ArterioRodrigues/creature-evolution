#include "game.h"
#include "configuration.h"
#include "creature.h"
#include "selection.h"
#include "simulation.h"
#include "text.h"

Game::Game() : _window(sf::VideoMode({Configuration::windowX, Configuration::windowY}), "Evolution Simultaion") {
  _x = Configuration::windowX;
  _y = Configuration::windowY;
  _fastForward = false;
}

void Game::run(int frameRate) {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time timePerFrame = sf::seconds(1.f / frameRate);
  while (_window.isOpen()) {
    processEvents();

    // timeSinceLastUpdate += clock.restart();
    // while (timeSinceLastUpdate > timePerFrame) {
    //   timeSinceLastUpdate -= timePerFrame;
    //   update(timePerFrame);
    // }
    //
    update(timePerFrame);
    render();
  }
}

void Game::processEvents() {
  std::optional<sf::Event> optionalEvent = _window.pollEvent();
  while (optionalEvent.has_value()) {
    sf::Event event = optionalEvent.value();
    if (event.is<sf::Event::Closed>())
      _window.close();

    else if (event.is<sf::Event::KeyPressed>()) {
      sf::Keyboard::Key code = event.getIf<sf::Event::KeyPressed>()->code;

      if (code == sf::Keyboard::Key::Escape)
        _window.close();
      else if (code == sf::Keyboard::Key::Space) {
        _fastForward = !_fastForward;
      }
    }
    optionalEvent = _window.pollEvent();
  }
}

void Game::update(sf::Time deltaTime) {

  if (_fastForward) {
    for (int i = 0; i < Configuration::fastFowardCount; i++) {
      _simulation.runOneStep();
      if (_simulation.getCurrentStep() >= Configuration::steps) _simulation.endOfGeneration();
    }
    return;
  }

  _simulation.runOneStep();
  if (_simulation.getCurrentStep() >= Configuration::steps) _simulation.endOfGeneration();
}

void Game::render() {
  Text gen(std::to_string(_simulation.getCurrentGeneration()));
  Text step(std::to_string(_simulation.getCurrentStep()), 30, 80);
  Text ff(_fastForward ? "FF" : "", 30, 130);

  _window.clear(sf::Color::White);
  _window.draw(_simulation.getWorld().getSelection());
  _window.draw(_simulation.getWorld().getSignal());
  for (Creature creature : _simulation.getWorld().getCreatures()) {
    _window.draw(creature);
  }

  _window.draw(gen);
  _window.draw(step);
  _window.draw(ff);
  _window.display();
}
