#include "sensors.h"
#include "compass.h"
#include "configuration.h"
#include "helper.h"
#include <bit>

static float handleSensorLPf(const Creature &self, World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  if (dx == 0 && dy == 0) return 0.0f;

  const int probeDist = self.getLongProbeDistance();
  if (probeDist <= 0) return 0.0f;

  int count = 0;
  for (int i = 1; i <= probeDist; ++i) {
    int x = self.getX() + dx * i;
    int y = self.getY() + dy * i;
    if (!world.getGrid().isInBounds(x, y)) break;
    if (world.getGrid().isOccupiedAt(x, y)) ++count;
  }
  return count / float(probeDist);
}

static float handleSensorLBf(const Creature &self, World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  if (dx == 0 && dy == 0) return 0.0f;

  const int probeDist = self.getLongProbeDistance();
  if (probeDist <= 0) return 0.0f;

  for (int i = 1; i <= probeDist; ++i) {
    int x = self.getX() + dx * i;
    int y = self.getY() + dy * i;
    if (!world.getGrid().isInBounds(x, y) || world.getGrid().isOccupiedAt(x, y)) {
      return 1.0f - float(i - 1) / float(probeDist);
    }
  }
  return 0.0f;
}

static float handleSensorGen(const Creature &self, World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  int x = self.getX() + dx;
  int y = self.getY() + dy;
  if (!world.getGrid().isInBounds(x, y) || !world.getGrid().isOccupiedAt(x, y)) return 0.0f;

  int neighborId = world.getGrid().at(x, y);
  auto &creatures = world.getCreatures();
  if (neighborId < 1 || neighborId > static_cast<int>(creatures.size())) return 0.0f;

  std::string a = self.getGenome().toString();
  std::string b = creatures[neighborId - 1].getGenome().toString();
  if (a.empty() || a.length() != b.length()) return 0.0f;

  int matchingBits = 0;
  const int totalBits = static_cast<int>(a.length()) * 4;
  for (size_t i = 0; i < a.length(); ++i) {
    int diff = hexToDecimal(a[i]) ^ hexToDecimal(b[i]);
    matchingBits += 4 - std::popcount(static_cast<unsigned int>(diff));
  }
  return float(matchingBits) / float(totalBits);
}

static float handleSensorOsc(const Creature &self, const World &world, int currentStep) {
  return (std::sin(2.0f * std::numbers::pi * currentStep / self.getOscillatorPeriod()) + 1.0f) / 2.0f;
}

static float handleSensorSlr(const Creature &self, World &world, int currentStep) {
  Compass heading = self.getLastMoveDir();
  auto [lx, ly] = compassToDelta(rotateLeft(heading));
  auto [rx, ry] = compassToDelta(rotateRight(heading));

  float result = 0.0f;
  for (int i = 1; i <= 3; i++) {
    result += world.getSignal().at(self.getX() + rx * i, self.getY() + ry * i);
    result -= world.getSignal().at(self.getX() + lx * i, self.getY() + ly * i);
  }
  return (result / 3.0f) / 255.0f;
}

static float handleSensorSfd(const Creature &self, World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  float result = 0.0f;
  for (int i = 1; i <= 3; i++) {
    result += world.getSignal().at(self.getX() + dx * i, self.getY() + dy * i);
  }
  return (result / 3.0f) / 255.0f;
}

static float handleSensorSg(const Creature &self, World &world, int currentStep) {
  return world.getSignal().at(self.getX(), self.getY()) / 255.0f;
}

static float handleSensorPop(const Creature &self, World &world, int currentStep) {
  int count = 0;
  for (int i = std::max(0, self.getX() - 3); i <= std::min(Configuration::gridWidth - 1, self.getX() + 3); i++) {
    for (int j = std::max(0, self.getY() - 3); j <= std::min(Configuration::gridHeight - 1, self.getY() + 3); j++) {
      if (i == self.getX() && j == self.getY()) continue;
      count += world.getGrid().isOccupiedAt(i, j) ? 1 : 0;
    }
  }
  return float(count) / 48.0f;
}

static float handleSensorBD(const Creature &self, const World &world, int currentStep) {
  int dist = std::min<int>({self.getX(), self.getY(), Configuration::gridWidth - 1 - self.getX(),
                            Configuration::gridHeight - 1 - self.getY()});
  float halfMin = std::min(Configuration::gridWidth, Configuration::gridHeight) / 2.0f;
  return dist / halfMin;
}

static float handleSensorBDy(const Creature &self, World &world, int currentStep) {
  return std::min<int>({self.getY(), Configuration::gridHeight - 1 - self.getY()}) /
         float(float(Configuration::gridHeight - 1) / 2);
}
static float handleSensorBDx(const Creature &self, World &world, int currentStep) {
  return std::min<int>({self.getX(), Configuration::gridWidth - 1 - self.getX()}) /
         float(float(Configuration::gridWidth - 1) / 2);
}

static float handleSensorBfd(const Creature &self, World &world, int currentStep) {
  auto [first, second] = compassToDelta(self.getLastMoveDir());
  int x = self.getX() + first;
  int y = self.getY() + second;

  if (!world.getGrid().isInBounds(x, y) || world.getGrid().isOccupiedAt(x, y)) return 1.0f;
  return 0.0f;
}

static float handleSensorBlr(const Creature &self, World &world, int currentStep) {
  Compass heading = self.getLastMoveDir();
  auto [lx, ly] = compassToDelta(rotateLeft(heading));
  auto [rx, ry] = compassToDelta(rotateRight(heading));

  int leftX = self.getX() + lx, leftY = self.getY() + ly;
  int rightX = self.getX() + rx, rightY = self.getY() + ry;

  bool leftBlocked = !world.getGrid().isInBounds(leftX, leftY) || world.getGrid().isOccupiedAt(leftX, leftY);
  bool rightBlocked = !world.getGrid().isInBounds(rightX, rightY) || world.getGrid().isOccupiedAt(rightX, rightY);

  return (int(rightBlocked) - int(leftBlocked) + 1) / 2.0f;
}

static float handleSensorPfd(const Creature &self, World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  int count = 0;
  for (int i = 1; i <= 3; ++i) {
    int x = self.getX() + dx * i;
    int y = self.getY() + dy * i;
    if (world.getGrid().isInBounds(x, y) && world.getGrid().isOccupiedAt(x, y)) ++count;
  }
  return count / 3.0f;
}

static float handleSensorPlr(const Creature &self, World &world, int currentStep) {
  Compass heading = self.getLastMoveDir();
  auto [lx, ly] = compassToDelta(rotateLeft(heading));
  auto [rx, ry] = compassToDelta(rotateRight(heading));

  int leftCount = 0, rightCount = 0;
  for (int i = 1; i <= 3; ++i) {
    int lX = self.getX() + lx * i, lY = self.getY() + ly * i;
    int rX = self.getX() + rx * i, rY = self.getY() + ry * i;
    if (world.getGrid().isInBounds(lX, lY) && world.getGrid().isOccupiedAt(lX, lY)) ++leftCount;
    if (world.getGrid().isInBounds(rX, rY) && world.getGrid().isOccupiedAt(rX, rY)) ++rightCount;
  }

  constexpr int maxCount = 3;
  return (rightCount - leftCount + maxCount) / float(2 * maxCount);
}

static float handleSensorLMx(const Creature &self, const World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  return (dx + 1) / 2.0f;
}
static float handleSensorLMy(const Creature &self, const World &world, int currentStep) {
  auto [dx, dy] = compassToDelta(self.getLastMoveDir());
  return (dy + 1) / 2.0f;
}

static float handleSensorRnd(const Creature &self, World &world, int currentStep) {
  return randomNumberGenerator(0.0f, 1.0f);
}
static float handleSensorAge(const Creature &self, World &world, int currentStep) {
  return currentStep / float(Configuration::steps);
}
static float handleSensorLx(const Creature &self, World &world, int currentStep) {
  return self.getX() / float(Configuration::gridWidth - 1);
}
static float handleSensorLy(const Creature &self, World &world, int currentStep) {
  return self.getY() / float(Configuration::gridHeight - 1);
}

float computeSensor(Neuron::Type sensorType, const Creature &self, World &world, int currentStep) {
  switch (sensorType) {
  case Neuron::Type::Slr:
    return handleSensorSlr(self, world, currentStep);
  case Neuron::Type::Sfd:
    return handleSensorSfd(self, world, currentStep);
  case Neuron::Type::Sg:
    return handleSensorSg(self, world, currentStep);
  case Neuron::Type::Age:
    return handleSensorAge(self, world, currentStep);
  case Neuron::Type::Rnd:
    return handleSensorRnd(self, world, currentStep);
  case Neuron::Type::Blr:
    return handleSensorBlr(self, world, currentStep);
  case Neuron::Type::Osc:
    return handleSensorOsc(self, world, currentStep);
  case Neuron::Type::Bfd:
    return handleSensorBfd(self, world, currentStep);
  case Neuron::Type::Plr:
    return handleSensorPlr(self, world, currentStep);
  case Neuron::Type::Pop:
    return handleSensorPop(self, world, currentStep);
  case Neuron::Type::Pfd:
    return handleSensorPfd(self, world, currentStep);
  case Neuron::Type::LPf:
    return handleSensorLPf(self, world, currentStep);
  case Neuron::Type::LMy:
    return handleSensorLMy(self, world, currentStep);
  case Neuron::Type::LMx:
    return handleSensorLMx(self, world, currentStep);
  case Neuron::Type::LBf:
    return handleSensorLBf(self, world, currentStep);
  case Neuron::Type::BDy:
    return handleSensorBDy(self, world, currentStep);
  case Neuron::Type::Gen:
    return handleSensorGen(self, world, currentStep);
  case Neuron::Type::BDx:
    return handleSensorBDx(self, world, currentStep);
  case Neuron::Type::BD:
    return handleSensorBD(self, world, currentStep);
  case Neuron::Type::Lx:
    return handleSensorLx(self, world, currentStep);
  case Neuron::Type::Ly:
    return handleSensorLy(self, world, currentStep);
  case Neuron::Type::LPD:
  case Neuron::Type::Kill:
  case Neuron::Type::OSC:
  case Neuron::Type::Res:
  case Neuron::Type::SENSORY:
  case Neuron::Type::INTERNAL:
  case Neuron::Type::ACTION:
  case Neuron::Type::MRL:
  case Neuron::Type::MX:
  case Neuron::Type::MY:
  case Neuron::Type::Mfd:
  case Neuron::Type::Mrn:
  case Neuron::Type::Mrv:
  case Neuron::Type::SG:
    return 0.5f;
  }
  return 0.5f;
}
