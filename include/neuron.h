#pragma once
#include "genome.h"
#include "pch.h"

#define SENSORY_TYPE_SIZE 21
#define ACTION_TYPE_SIZE 11

class Neuron {
public:
  enum Type {
    SENSORY,
    INTERNAL,
    ACTION,

    Slr, // PheromoneGradientLeftToRight,
    Sfd, // PheromoneGradientFoward,
    Sg,  // PheromoneDensity,
    Age, // Age,
    Rnd, // RandomInput,
    Blr, // BlockageLeftToRight,
    Osc, // Oscillator,
    Bfd, // BlockageForward,
    Plr, // PopulationGradientLeftToRight,
    Pop, // PopulationDensity,
    Pfd, // PopulationGradientForward,
    LPf, // PopulationLongRangeForward,
    LMy, // LastMovementY,
    LMx, // LastMovementX,
    LBf, // BlockageLongRangeForward,
    BDy, // NorthSouthBorderDistance,
    Gen, // GeneticSimilarityOfForwardNeighbor,
    BDx, // EastWestBorderLocation,
    BD,  // NearestBorderDistance,
    Lx,  // EastWestWorldLocation,
    Ly,  // NorthSouthWorldLocation

    LPD,  // Set Long Probe Distance
    Kill, // Kill forward neighbor
    OSC,  // Set oscillator period
    SG,   // Emit pheromone
    Res,  // set responsiveness
    Mfd,  // move forward
    Mrn,  // move random
    Mrv,  // move reverse
    MRL,  // move left/right
    MX,   // move east/west
    MY,   // move north/south
          //
  };

  Neuron(Type type, int id, int internalNeuronCount) {
    _internalId = -1;
    if (type == Type::SENSORY)
      _neuron = Neuron::Type(id % SENSORY_TYPE_SIZE + 3);
    else if (type == Type::ACTION)
      _neuron = Neuron::Type(id % ACTION_TYPE_SIZE + 23);
    else {
      _neuron = Neuron::Type::INTERNAL;
      _internalId = id % internalNeuronCount;
    }
  }

  const Neuron::Type getNeuron() { return _neuron; }
  const int getInternalId() { return _internalId; }

  friend std::ostream &operator<<(std::ostream &os, Neuron &neuron) {
    switch (neuron.getNeuron()) {
    case (Neuron::Type::SENSORY):
      os << "SENSORY";
      break;
    case (Neuron::Type::INTERNAL):
      os << "INTERNAL " << neuron.getInternalId();
      break;
    case (Neuron::Type::ACTION):
      os << "ACTION";
      break;
    case (Neuron::Type::Slr):
      os << "Slr";
      break;
    case (Neuron::Type::Sfd):
      os << "Sfd";
      break;
    case (Neuron::Type::Sg):
      break;
    case (Neuron::Type::Age):
      os << "Age";
      break;
    case (Neuron::Type::Rnd):
      os << "Rnd";
      break;
    case (Neuron::Type::Blr):
      os << "Blr";
      break;
    case (Neuron::Type::Osc):
      os << "Osc";
      break;
    case (Neuron::Type::Bfd):
      os << "Bfd";
      break;
    case (Neuron::Type::Plr):
      os << "Plr";
      break;
    case (Neuron::Type::Pop):
      os << "Pop";
      break;
    case (Neuron::Type::Pfd):
      os << "Pfd";
      break;
    case (Neuron::Type::LPf):
      os << "LPf";
      break;
    case (Neuron::Type::LMy):
      os << "LMy";
      break;
    case (Neuron::Type::LMx):
      os << "LMx";
      break;
    case (Neuron::Type::LBf):
      os << "LBf";
      break;
    case (Neuron::Type::BDy):
      os << "BDy";
      break;
    case (Neuron::Type::Gen):
      os << "Gen";
      break;
    case (Neuron::Type::BDx):
      os << "BDx";
      break;
    case (Neuron::Type::BD):
      os << " BD";
      break;
    case (Neuron::Type::Lx):
      os << " Lx";
      break;
    case (Neuron::Type::Ly):
      os << " Ly";
      break;
    case (Neuron::Type::LPD):
      os << "LPD";
      break;
    case (Neuron::Type::Kill):
      os << "Kill";
      break;
    case (Neuron::Type::OSC):
      os << "OSC";
      break;
    case (Neuron::Type::SG):
      os << " SG";
      break;
    case (Neuron::Type::Res):
      os << "Res";
      break;
    case (Neuron::Type::Mfd):
      os << "Mfd";
      break;
    case (Neuron::Type::Mrn):
      os << "Mrn";
      break;
    case (Neuron::Type::Mrv):
      os << "Mrv";
      break;
    case (Neuron::Type::MRL):
      os << "MRL";
      break;
    case (Neuron::Type::MX):
      os << "MX";
      break;
    case (Neuron::Type::MY):
      os << "MY";
      break;
    }
    return os;
  }

private:
  Neuron::Type _neuron;
  int _internalId;
};
