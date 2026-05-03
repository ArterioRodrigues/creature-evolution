# Creature Simulation

An evolution simulator where creatures' brains are encoded directly in their genome. Each creature carries a hex-string of DNA that decodes into a small neural network: sensors on one side, motor actions on the other, with internal neurons in between. Run a population, let selection pressure pick winners, mutate the survivors, and watch behavior emerge over generations.

Inspired by [biosim4](https://github.com/davidrmiller/biosim4).

## How it works

A creature's genome is a string of hex digits. Each 8-character chunk is one **gene**, and each gene encodes one connection in the creature's neural network:

```
A3F2B91C
│└┬┘│└┬┘
│ │ │ └─ weight (16 bits, signed)
│ │ └─── sink type bit + sink ID (8 bits)
│ └───── source ID (7 bits)
└─────── source type bit (1 bit: sensory or internal)
```

When a creature is born, its genome decodes into a list of `(source, sink, weight)` connections. Sources are either **sensory neurons** (21 of them — position, age, population density, blockage, pheromones, etc.) or internal neurons. Sinks are either internal neurons or **action neurons** (11 of them — move forward, turn, kill, emit pheromone, etc.).

Before the brain is used, useless connections are **pruned**: internal neurons with no inputs always output zero, and ones with no outputs are wasted compute. Both get removed, and removing one can orphan another, so the prune iterates until stable. Surviving internal neurons are then renumbered to dense indices.

Each simulation step, the brain runs a feed-forward pass:

1. Compute every sensor that's actually wired up
2. Feed internal neurons (using last step's internal state, which lets feedback loops work)
3. `tanh` the internal accumulators to get this step's internal state
4. Feed action neurons using the fresh internal state
5. `tanh` the action accumulators — these are the motor outputs

Action levels in `[-1, 1]` drive what the creature does next.

## Build

Requires CMake 3.28+, a C++17 compiler, and Python 3 with NumPy (used for plotting).

```bash
./run.sh
```

That script runs `cmake -B build`, builds, and launches the sim. SFML 3.0.2 is fetched automatically by CMake.

If you want to set up your editor's LSP:

```bash
ln -s build/compile_commands.json .
```

## Project layout

```
include/
  configuration.h    # Global sim parameters
  creature.h         # Individual creature: position, color, genome, brain
  game.h             # SFML window, main loop
  genome.h           # Hex genome generation and gene decoding
  neuralNetwork.h    # Connection list, prune, feed-forward
  neuron.h           # Neuron type enum (sensors, internals, actions)
  world.h            # Population container
  helper.h           # RNG, hex/decimal conversion
  pch.h              # Precompiled includes (SFML, STL)
src/
  *.cpp              # Implementations
run.sh               # cmake build + launch
CMakeLists.txt
```

## Configuration

Edit `src/configuration.cpp` to tune the simulation:

| Field            | Default | Meaning                                |
| ---------------- | ------- | -------------------------------------- |
| `windowX/Y`      | 1000×800 | Window dimensions in pixels           |
| `population`     | 1       | Number of creatures per generation    |
| `steps`          | 300     | Steps per generation                  |
| `genomeLength`   | 4       | Genes per creature                    |
| `neurons`        | 1       | Internal neurons per brain (max)      |
| `mutation`       | 0.01    | Per-bit mutation rate                 |
| `frameRate`      | 30      | Render FPS                            |

## Status

Working:
- Genome generation and decoding
- Neural network construction with pruning and renumbering
- Feed-forward pass with recurrent internal state
- SFML window and per-frame rendering of creatures

In progress:
- Sensor implementations (currently stubbed at 0)
- Action handlers (movement, kill, pheromone emission)
- Generational selection and mutation
- World grid for collision and population sensors
- Pheromone diffusion

## Controls

- `Esc` — quit

## License

TBD.
