#include "grid.h"
#include "configuration.h"

Grid::Grid(int width, int height) {
  this->_width = width;
  this->_height = height;

  for (int i = 0; i < width; i++) {
    std::vector<int16_t> row;
    for (int j = 0; j < height; j++) {
      if (Configuration::barrier == BarrierType::VeriticalBar)
        row.push_back(i > 60 && i < 70 && j > 30 && j < 90 ? -1 : 0);
      if (Configuration::barrier == BarrierType::HorizontalBar)
        row.push_back(i > 30 && i < 90 && j > 60 && j < 70 ? -1 : 0);
      else
        row.push_back(0);
    }

    _cells.push_back(row);
  }
}

bool Grid::isInBounds(int x, int y) const { return x >= 0 && x < _width && y >= 0 && y < _height; }

bool Grid::isEmptyAt(int x, int y) const { return isInBounds(x, y) && _cells[x][y] == 0; }

bool Grid::isOccupiedAt(int x, int y) const { return isInBounds(x, y) && _cells[x][y] > 0; }

int16_t Grid::at(int x, int y) const { return _cells[x][y]; }
void Grid::set(int x, int y, int16_t value) { _cells[x][y] = value; }
void Grid::move(int fromX, int fromY, int toX, int toY) {
  _cells[toX][toY] = _cells[fromX][fromY];
  _cells[fromX][fromY] = 0;
}

int Grid::getWidth() const { return _width; }
int Grid::getHeight() const { return _height; }

void Grid::clear() {
  for (int i = 0; i < _width; i++)
    for (int j = 0; j < _height; j++)
      if (_cells[i][j] != -1) set(i, j, 0);
}

bool Grid::isBarrierAt(int x, int y) { return isInBounds(x, y) && at(x, y) > 0; }
void Grid::setBarrier(int x, int y) {
  if (isInBounds(x, y)) set(x, y, -1);
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  const float cellW = Configuration::windowX / static_cast<float>(_width);
  const float cellH = Configuration::windowY / static_cast<float>(_height);

  sf::RectangleShape rect;
  rect.setSize({cellW, cellH});

  for (int x = 0; x < _width; ++x) {
    for (int y = 0; y < _height; ++y) {
      if (_cells[x][y] != -1) continue;

      rect.setPosition({x * cellW, y * cellH});
      rect.setFillColor(sf::Color(80, 80, 80));
      target.draw(rect, states);
    }
  }
}
