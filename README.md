Escape Protocol

A pursuit-evasion game on a dynamically directed, weighted graph, written in C++ with SFML. You play as a ship in a procedurally generated solar system, moving from point to point along the graph while a pursuer hunts you down. The pursuer always knows the shortest path to you — because it computes it.

(screenshot here — a mid-game shot showing the graph and both ships)

The Pathfinding

The interesting problem in this project is the graph, not the spaceships.


The solar system is generated procedurally, and gravitational forces determine the edge weights — which means edge weights can be negative.
Edge directions are dynamic: the graph changes as the game runs.
Because of the negative weights, Dijkstra's algorithm doesn't apply. The pursuer instead uses my own implementation of the Bellman-Ford algorithm to find the shortest path to the player.
The pursuer recomputes Bellman-Ford every time the player moves, so it is always chasing along a current shortest path, never a stale one.


This extends the classical cops-and-robbers game to a directed graph with changing directions and mixed-sign weights. The full write-up — motivation, architecture, testing, and future directions — is in Final Report.pdf, written for CSC 375 at the University of Michigan–Flint.

How to Play


Click a connected point (within one ring of your current position) to move there. Every move you make triggers the pursuer to recompute its path and advance.
WASD pans the camera.
If the pursuer reaches your point, the game is over.


Architecture

The game runs on an enum-based state machine (GameState.h) with four states — StartScreen, LevelSelect, Playing, GameOver — so each screen owns its logic and rendering, and transitions happen in exactly one place.

Building

SFML is fetched and built automatically by CMake (FetchContent), so there's nothing to install beyond a compiler and CMake itself.

cmake -B build
cmake --build build

The executable lands in build/bin/ with the assets copied next to it.

On Linux, install SFML's dependencies first:

sudo apt update
sudo apt install libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
    libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev

On Windows, opening the folder in Visual Studio (with the CMake component installed) configures and builds automatically.

Builds are verified on Windows, Linux, and macOS by the CI workflow in this repo.

License

Dual licensed under Public Domain and MIT — see LICENSE.md.
