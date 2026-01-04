#pragma once

class Neurons {
public:
  enum Sensory {
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
  };

  enum Action {
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
  };
};
