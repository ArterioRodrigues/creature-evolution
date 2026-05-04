#include "signal.h"
#include "configuration.h"

Signal::Signal(int width, int height) {
  this->_width = width;
  this->_height = height;

  for (int i = 0; i < width; i++) {
    std::vector<uint8_t> row;
    for (int j = 0; j < height; j++) {
      row.push_back(0);
    }
    _cells.push_back(row);
  }
}

void Signal::emit(int x, int y, int radius, uint8_t amount) {
  for (int i = std::max(0, x - radius); i < std::min(_width, x + radius); i++) {
    for (int j = std::max(0, y - radius); j < std::min(_height, y + radius); j++) {
      int sum = static_cast<int>(_cells[i][j]) + static_cast<int>(amount);
      _cells[i][j] = static_cast<uint8_t>(std::min(255, sum));
    }
  }
}

int16_t Signal::at(int x, int y) const {
  if (x < 0 || x >= _width || y < 0 || y >= _height) return 0;
  return _cells[x][y];
}

void Signal::set(int x, int y, uint8_t value) {
  if (x < 0 || x >= _width || y < 0 || y >= _height) return;
  _cells[x][y] = value;
}

int Signal::getWidth() const { return _width; }
int Signal::getHeight() const { return _height; }

void Signal::clear() {
  for (int i = 0; i < _width; i++)
    for (int j = 0; j < _height; j++) set(i, j, 0);
}

void Signal::decay() {
  for (int i = 0; i < _width; i++) {
    for (int j = 0; j < _height; j++) {
      _cells[i][j] = static_cast<uint8_t>(std::max(0.0f, _cells[i][j] - Configuration::decayRate));
    }
  }
}

void Signal::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  const float cellW = Configuration::windowX / static_cast<float>(_width);
  const float cellH = Configuration::windowY / static_cast<float>(_height);

  sf::RectangleShape rect;
  rect.setSize({cellW, cellH});

  for (int x = 0; x < _width; ++x) {
    for (int y = 0; y < _height; ++y) {
      uint8_t v = _cells[x][y];
      if (v == 0) continue;

      rect.setPosition({x * cellW, y * cellH});
      rect.setFillColor(sf::Color(0, 255, 0, v));
      target.draw(rect, states);
    }
  }
}
