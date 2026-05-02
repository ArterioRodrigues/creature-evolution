#include "grid.h"

Grid::Grid(int width, int height) {
  this->_width = width;
  this->_height = height;

  for (int i = 0; i < width; i++) {
    std::vector<int16_t> row;
    for (int j = 0; j < height; j++) {
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
