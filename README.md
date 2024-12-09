# R-Type

## Description

This project is a recreation of the R-Type game using our own custom game engine.
Inspired by the classic **Shoot'em'up** genre, players take control of a spaceship to combat waves of enemies and challenging bosses.

---

## Table of contents

-   [Prerequisites](#Prerequisites)
-   [Run the game](#run-the-game)
-   [Project structure](#project-structure)

---

## Prerequisites

Before getting started, make sure you have the following installed on your machine:
- A C++ compiler supporting C++17

1. Clone the repository:

    ```bash
    git clone git@github.com:EpitechPromo2027/B-CCP-500-TLS-5-2-rtype-anastasia.bouby.git
    cd B-CCP-500-TLS-5-2-rtype-anastasia.bouby
    ```

2. Build the project:
    ```bash
    cmake -B build .
    cd build/
    make
    ```
---

## Run the game

1. Start the Network Server:

    Make sure to be in **B-CCP-500-TLS-5-2-rtype-anastasia.bouby/build/**

    ```bash
    cd network/
    ./Network
    ```

2. Start the Client:

    Open a new terminal and make sure to be in **B-CCP-500-TLS-5-2-rtype-anastasia.bouby/build/**

    ```bash
    cd client/
    ./Client
    ```
---

## Project structure

`assets/`: Game resources such as textures, sounds.

`client/`: Contains the client-side game logic and graphics.

`external/`: External library needed.

`game_engine/`: Handles server-side game_engine.

`network/`: Handles server-side networking.

