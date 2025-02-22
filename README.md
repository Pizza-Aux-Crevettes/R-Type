# R-Type

## Description

This project is a recreation of the R-Type game using our own custom game engine.
Inspired by the classic **Shoot'em'up** genre, players take control of a spaceship to combat waves of enemies and challenging bosses.

You can check the online documentation to this url : "https://pizza-aux-crevettes.github.io/R-Type/clang-format.html"

---

## Table of contents

- [Prerequisites](#Prerequisites)
- [Run the game](#run-the-game)
- [Project structure](#project-structure)

---

## Prerequisites

Before getting started, make sure you have the following installed on your machine:

- A C++ compiler supporting C++17

1. Clone the repository:

   ```bash
   git clone --recurse-submodules git@github.com:EpitechPromo2027/B-CCP-500-TLS-5-2-rtype-anastasia.bouby.git
   cd B-CCP-500-TLS-5-2-rtype-anastasia.bouby
   ```

2. Install UDev library (if necessary)

   On ubuntu:

   ```bash
   sudo apt install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev libcriterion-dev libfreetype-dev libfreetype6 libfreetype6-dev git gcc g++ make cmake
   ```

   On fedora:

   ```bash
   sudo dnf install freetype-devel libglvnd-opengl libXrandr-devel libXcursor-devel xrandr freetype glew libjpeg-turbo libsndfile openal-soft libvorbis-devel flac-devel libX11-devel libGL-devel systemd-devel openal-soft-devel git gcc g++ make cmake
   ```

3. Build the project:
   ```bash
   cmake -B build .
   cd build/
   make
   ```

---

## Run the game

1. Start the Server:

   Make sure to be in **B-CCP-500-TLS-5-2-rtype-anastasia.bouby/**

   ```bash
   ./build/server/Server
   ```

2. Start the Client:

   Open a new terminal and make sure to be in **B-CCP-500-TLS-5-2-rtype-anastasia.bouby/**

   ```bash
   ./build/client/Client
   ```

---

## Project structure

`assets/`: Game resources such as textures, sounds.

`client/`: Contains the client-side game logic and graphics.

`external/`: External library needed.

`game_engine/`: Handles server-side game_engine.

`server/`: Handles server-side networking.
