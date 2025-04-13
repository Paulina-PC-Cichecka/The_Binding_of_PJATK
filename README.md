# The Binding of PJATK

The Binding of PJATK is a humorous 2D game parody inspired by The Binding of Isaac, developed as a C++ course project. The game uses [SFML library](https://github.com/SFML/SFML) version 2.6.1, [FMT library](https://github.com/fmtlib/fmt) version 10.2.1 and a custom engine.

## Features

- Custom engine (that makes implementing and extending the features of the game easier)
- Custom enemies based on university teachers
- Randomized number of opponents
- Various power-ups that affect player stats
  
![power-up](https://github.com/user-attachments/assets/e1fa2dee-a248-456f-b6c3-beadaf2b0289)

- Projectile shooting mechanic
  
![projectile-shooting](https://github.com/user-attachments/assets/786742ab-78a3-4d08-b61b-a1910f0ab8d8)

- Dealing and receiving damage

![koniec-gry](https://github.com/user-attachments/assets/8d930982-ea7d-4729-bdef-e2d6fd49f764)

## About the game engine

This game uses a custom-built engine written entirely in C++.

The engine handles:

- Scene and entity management
- Collision detection
- Resource loading
- Sprite rendering
- Input handling
- Saving and loading system

### Save and load system

The game features a simple yet effective save/load system, allowing players to:

- Save the current game state
- Resume from a previously saved game session
- Preserve player stats, inventory, room layout, and more

Save files are **stored locally** and can be used to return to your run.

![zapisywanie-stanu-i-wczytywanie](https://github.com/user-attachments/assets/aa0a14a7-d4e1-4ca6-8f20-04e67c58cc3d)


## Requirements

- C++20 or newer
- CMake 3.28 or newer
- SFML 2.6.1 or newer
- FMT 10.2.1 or newer
- Sceen resolution 2880 x 1920 - by default (planned change to dynamic)
