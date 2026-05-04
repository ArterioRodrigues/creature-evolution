#include "selection.h"
#include "configuration.h"
#include "creature.h"

namespace {
constexpr sf::Color kZoneColor(0, 255, 0, 50);

inline float cellW() { return Configuration::windowX / float(Configuration::gridWidth); }
inline float cellH() { return Configuration::windowY / float(Configuration::gridHeight); }
} // namespace

bool Selection::survives(const Creature &c, const World &world) {
  const int x = c.getX();
  const int y = c.getY();
  const int W = Configuration::gridWidth;
  const int H = Configuration::gridHeight;

  switch (Configuration::selection) {
  case SelectionType::RightHalf:
    return x > W / 2;

  case SelectionType::LeftHalf:
    return x < W / 2;

  case SelectionType::CenterSquare: {
    const int qw = W / 4;
    const int qh = H / 4;
    return x >= qw && x < W - qw && y >= qh && y < H - qh;
  }

  case SelectionType::CenterCircle: {
    const float cx = W / 2.0f;
    const float cy = H / 2.0f;
    const float r = std::min(W, H) / 4.0f;
    const float ddx = x - cx;
    const float ddy = y - cy;
    return ddx * ddx + ddy * ddy <= r * r;
  }

  case SelectionType::Corners: {
    const int m = std::min(W, H) / 6;
    const bool xnear = (x < m) || (x >= W - m);
    const bool ynear = (y < m) || (y >= H - m);
    return xnear && ynear;
  }

  case SelectionType::HorizontalBand: {
    const int band = H / 6;
    return y >= H / 2 - band && y < H / 2 + band;
  }

  case SelectionType::VerticalBand: {
    const int band = W / 6;
    return x >= W / 2 - band && x < W / 2 + band;
  }

  case SelectionType::EastWestEdges: {
    const int m = W / 6;
    return x < m || x >= W - m;
  }
  }
  return false;
}

void Selection::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  const float cw = cellW();
  const float ch = cellH();
  const int W = Configuration::gridWidth;
  const int H = Configuration::gridHeight;

  auto drawRect = [&](float px, float py, float pw, float pheight) {
    sf::RectangleShape rect({pw, pheight});
    rect.setPosition({px, py});
    rect.setFillColor(kZoneColor);
    target.draw(rect, states);
  };

  switch (Configuration::selection) {
  case SelectionType::RightHalf:
    drawRect((W / 2) * cw, 0.0f, (W - W / 2) * cw, H * ch);
    break;

  case SelectionType::LeftHalf:
    drawRect(0.0f, 0.0f, (W / 2) * cw, H * ch);
    break;

  case SelectionType::CenterSquare: {
    const int qw = W / 4;
    const int qh = H / 4;
    drawRect(qw * cw, qh * ch, (W - 2 * qw) * cw, (H - 2 * qh) * ch);
    break;
  }

  case SelectionType::CenterCircle: {
    // Use the tighter axis to keep the disk circular even on non-square cells.
    const float r = std::min(W, H) / 4.0f;
    const float pixelR = r * std::min(cw, ch);
    sf::CircleShape circ(pixelR);
    circ.setPosition({(W / 2.0f) * cw - pixelR, (H / 2.0f) * ch - pixelR});
    circ.setFillColor(kZoneColor);
    target.draw(circ, states);
    break;
  }

  case SelectionType::Corners: {
    const int m = std::min(W, H) / 6;
    drawRect(0.0f, 0.0f, m * cw, m * ch);
    drawRect((W - m) * cw, 0.0f, m * cw, m * ch);
    drawRect(0.0f, (H - m) * ch, m * cw, m * ch);
    drawRect((W - m) * cw, (H - m) * ch, m * cw, m * ch);
    break;
  }

  case SelectionType::HorizontalBand: {
    const int band = H / 6;
    drawRect(0.0f, (H / 2 - band) * ch, W * cw, 2 * band * ch);
    break;
  }

  case SelectionType::VerticalBand: {
    const int band = W / 6;
    drawRect((W / 2 - band) * cw, 0.0f, 2 * band * cw, H * ch);
    break;
  }

  case SelectionType::EastWestEdges: {
    const int m = W / 6;
    drawRect(0.0f, 0.0f, m * cw, H * ch);
    drawRect((W - m) * cw, 0.0f, m * cw, H * ch);
    break;
  }
  }
}
