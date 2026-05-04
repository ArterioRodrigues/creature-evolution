#include "actions.h"
#include "compass.h"
#include "helper.h"

void executeActions(Creature &self, World &world, const std::unordered_map<Neuron::Type, float> &actionLevels,
                    int currentStep) {
  float dx = 0;
  float dy = 0;

  for (const auto &[actionType, level] : actionLevels) {
    if (actionType == Neuron::Type::MX) dx += level;
    if (actionType == Neuron::Type::MY) dy += level;
    if (actionType == Neuron::Type::Mfd) {
      auto [fdx, fdy] = compassToDelta(self.getLastMoveDir());
      dx += level * fdx;
      dy += level * fdy;
    }
    if (actionType == Neuron::Type::Mrv) {
      auto [fdx, fdy] = compassToDelta(self.getLastMoveDir());
      dx -= level * fdx;
      dy -= level * fdy;
    }
    if (actionType == Neuron::Type::Mrn) {
      Compass d = Compass(randomNumberGenerator(0, 7));
      auto [fdx, fdy] = compassToDelta(d);
      dx += level * fdx;
      dy += level * fdy;
    }
    if (actionType == Neuron::Type::MRL) {
      Compass rightDir = rotateRight(self.getLastMoveDir());
      auto [rdx, rdy] = compassToDelta(rightDir);
      dx += level * rdx;
      dy += level * rdy;
    }
    if(actionType == Neuron::Type::SG) 
        world.getSignal().emit(self.getX(), self.getY(), randomNumberGenerator(1, 3), randomNumberGenerator(0, 255));
  }

  float probX = std::tanh(std::abs(dx));
  float probY = std::tanh(std::abs(dy));

  int stepX = 0;
  int stepY = 0;

  if (randomNumberGenerator(0.0f, 1.0f) < probX) stepX = (dx > 0) ? 1 : -1;
  if (randomNumberGenerator(0.0f, 1.0f) < probY) stepY = (dy > 0) ? 1 : -1;

  if (stepX == 0 && stepY == 0) return;

  int newX = self.getX() + stepX;
  int newY = self.getY() + stepY;

  Grid &grid = world.getGrid();

  if (!grid.isInBounds(newX, newY) || !grid.isEmptyAt(newX, newY)) return;

  grid.move(self.getX(), self.getY(), newX, newY);
  self.setLocation(newX, newY);

  Compass newDir = deltaToCompass(stepX, stepY);
  self.setLastMoveDir(newDir);
  return;
}
