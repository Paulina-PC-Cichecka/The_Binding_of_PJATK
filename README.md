# The Binding of PJATK

The Binding of PJATK is a humorous 2D game parody inspired by The Binding of Isaac, developed as a student project. The game uses SFML library and custom engine.


## About the game engine

This game uses a custom-built engine written entirely in C++

The engine handles:

- Scene and entity management
- Collision detection
- Resource loading
- Sprite rendering
- Input handling
- Saving and loading system


### Save and load system

The game features a simple yet effective save/load system, allowing players to:

- Save the current game state at key points
- Resume from a previously saved game session
- Preserve player stats, inventory, room layout, and more

Save files are **stored locally** and can be used to return to your run


## Features

- Custom engine (that makes writing a game easier)
- Custom enemies
- Randomized number of opponents
- Various power-ups that affect player stats
- Projectile shooting mechanic
- Giving and receiving damage


## Requirements

- C++20 or newer
- CMake 3.28 or newer
- SFML 2.6.1 or newer
- Sceen resolution 2880 x 1920 - by default (planned change to dynamic)
