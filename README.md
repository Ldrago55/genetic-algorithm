#  Genetic Algorithm in C++

A simple 3D simulation of genetic algorithm where agents evolve their brain (neural networks) to move towards a target.

![License](https://img.shields.io/badge/license-MIT-blue.svg)

---

## Demo
[demo video](https://github.com/user-attachments/assets/4bf6be1c-eb6b-48f7-b812-52694a87133f)

---

##  Features

*   **Neural Networks**: Each agent is powered by a feed-forward brain (`topology: 6-8-2`).
*   **Genetic Evolution**: Population evolves through fitness-based selection, crossover and mutation.
*   **3D Environment**: Real-time visualization using [Raylib](https://www.raylib.com/).
*   **Lightweight**: Pure C++ with only 1 dependency for visualization (Raylib).

##  Quick Start

### Dependencies

Ensure you have the following installed:
*   `g++`
*   `make`
*   `raylib`

### Build & Run

```bash
# Clone the repository
git clone https://github.com/Ldrago55/genetic-algorithm.git
cd genetic-algorithm

# Build the project
make

# Run the simulation
./build/main
```

##  Controls

*   **Mouse**: Look around (First Person Camera).
*   **WASD**: Move camera.
*   **ESC**: Exit simulation.

##  Architecture

- `src/nn/`: Neural network implementation.
- `src/agent/`: Agent logic and "brain" integration.
- `src/population/`: Evolution and population management.
- `src/env/`: 3D world and fitness evaluation.
