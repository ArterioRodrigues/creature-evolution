#include "sensors.h"
#include "compass.h"
#include "configuration.h"
#include "helper.h"

static float handleSensorOsc(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorLPf(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorLBf(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorGen(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorLPD(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorKill(const Creature &self, const World &world, int currentStep) { return 0.5f; }
static float handleSensorRes(const Creature &self, const World &world, int currentStep) { return 0.5f; }

static float handleSensorSlr(const Creature &self, World world, int currentStep) {
  float result = 0;
  for (int i = 0; i < 3; i++) {
    result += world.getSignal().at(self.getX(), self.getY() + i);
  }

  for (int i = 0; i < 3; i++) {
    result -= world.getSignal().at(self.getX(), self.getY() - i);
  }
  return result / 3;
}

static float handleSensorSfd(const Creature &self, World &world, int currentStep) {
  float result = 0;
  for (int i = 0; i < 3; i++) {
    result += world.getSignal().at(self.getX(), self.getY() + i);
  }
  return result / 3;
}

static float handleSensorSg(const Creature &self, World &world, int currentStep) {
  return world.getSignal().at(self.getX(), self.getY());
}
static float handleSensorPop(const Creature &self, World &world, int currentStep) {
  int count = 0;
  for (int i = std::max(0, self.getX() - 3); i < std::min(Configuration::gridWidth, self.getX() + 3); i++) {
    for (int j = std::max(0, self.getY() - 3); j < std::min(Configuration::gridHeight, self.getY() + 3); j++)
      count += world.getGrid().isOccupiedAt(i, j) ? 1 : 0;
  }
  return float(count) / 48.0f;
}
static float handleSensorBD(const Creature &self, const World &world, int currentStep) {
  return std::min<int>({self.getX(), self.getY(), Configuration::gridWidth - 1 - self.getX(),
                        Configuration::gridHeight - 1 - self.getY()}) -
         float(float(std::min<int>(Configuration::gridWidth, Configuration::gridHeight)) / 2);
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

  if (world.getGrid().isOccupiedAt(x, y) || world.getGrid().isInBounds(x, y)) return 1.0f;
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
  return randomNumberGenerator(0.0f, 0.0f);
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
static float handleSensorOSC(const Creature &self, World &world, int currentStep) {
  return (std::sin(2.0f * std::numbers::pi * currentStep / 34.0f) + 1.0f) / 2.0f;
}
float computeSensor(Neuron::Type sensorType, const Creature &self, World &world, int currentStep) {
  switch (sensorType) {
  case Neuron::Type::Slr:
    return handleSensorSlr(self, world, currentStep);
    break;
  case Neuron::Type::Sfd:
    return handleSensorSfd(self, world, currentStep);
    break;
  case Neuron::Type::Sg:
    return handleSensorSg(self, world, currentStep);
    break;
  case Neuron::Type::Age:
    return handleSensorAge(self, world, currentStep);
    break;
  case Neuron::Type::Rnd:
    return handleSensorRnd(self, world, currentStep);
    break;
  case Neuron::Type::Blr:
    return handleSensorBlr(self, world, currentStep);
    break;
  case Neuron::Type::Osc:
    return handleSensorOsc(self, world, currentStep);
    break;
  case Neuron::Type::Bfd:
    return handleSensorBfd(self, world, currentStep);
    break;
  case Neuron::Type::Plr:
    return handleSensorPlr(self, world, currentStep);
    break;
  case Neuron::Type::Pop:
    return handleSensorPop(self, world, currentStep);
    break;
  case Neuron::Type::Pfd:
    return handleSensorPfd(self, world, currentStep);
    break;
  case Neuron::Type::LPf:
    return handleSensorLPf(self, world, currentStep);
    break;
  case Neuron::Type::LMy:
    return handleSensorLMy(self, world, currentStep);
    break;
  case Neuron::Type::LMx:
    return handleSensorLMx(self, world, currentStep);
    break;
  case Neuron::Type::LBf:
    return handleSensorLBf(self, world, currentStep);
    break;
  case Neuron::Type::BDy:
    return handleSensorBDy(self, world, currentStep);
    break;
  case Neuron::Type::Gen:
    return handleSensorGen(self, world, currentStep);
    break;
  case Neuron::Type::BDx:
    return handleSensorBDx(self, world, currentStep);
    break;
  case Neuron::Type::BD:
    return handleSensorBD(self, world, currentStep);
    break;
  case Neuron::Type::Lx:
    return handleSensorLx(self, world, currentStep);
    break;
  case Neuron::Type::Ly:
    return handleSensorLy(self, world, currentStep);
    break;
  case Neuron::Type::LPD:
    return handleSensorLPD(self, world, currentStep);
    break;
  case Neuron::Type::Kill:
    return handleSensorKill(self, world, currentStep);
    break;
  case Neuron::Type::OSC:
    return handleSensorOSC(self, world, currentStep);
    break;
  case Neuron::Type::Res:
    return handleSensorRes(self, world, currentStep);
    break;
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
    break;
  }
}
