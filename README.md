# Palwish - 3D Raycasting Game Engine

A multiplayer first-person shooter game engine written in C using CSFML, featuring raycasting technology similar to classic games like Wolfenstein 3D.

## Features

- First-person 3D perspective using raycasting
- Multiplayer capabilities with client-server architecture
- Real-time network synchronization
- Multiple weapons system (AK47, Minigun)
- Smooth player movement and rotation
- Real-time rendered minimap with player tracking
- Procedurally generated maps
- Advanced collision detection
- Textured walls, floor, and ceiling
- Mouse and gamepad support
- Health and stamina systems
- Weapon reloading mechanics
- Performance statistics display

## Prerequisites

- GCC compiler
- CSFML library
- Make
- Network connectivity (for multiplayer)

## Building

To build the project:
```bash
make
```

To run in offline mode:
```bash
./wolf3d y
```

To run in online mode:
```bash
./wolf3d
```

## Controls

### Keyboard/Mouse
- W/Z or Up Arrow: Move forward
- S or Down Arrow: Move backward
- A/Q or Left Arrow: Strafe left
- D or Right Arrow: Strafe right
- Mouse: Aim/Look around
- Left Click: Shoot
- R: Reload weapon
- 1-2: Switch weapons
- Left Shift: Sprint
- ESC: Exit game
- P: Pause game

### Gamepad
- Left Stick: Movement
- Right Stick: Look around
- RT: Shoot
- RB: Reload
- LB: Sprint
- Back: Exit game

## Network Features

- Real-time player position synchronization
- Player health synchronization
- Weapon damage system
- Server-side object management
- Low-latency communication
- Automatic reconnection handling

## Project Structure

- `src/`: Source files
    - `main.c`: Main game loop and initialization
    - `network/`: Networking components
    - `events/`: Input handling and game events
    - `draw/`: Rendering systems
    - `maps/`: Procedural map generation
    - `menu/`: Menu and UI systems
- `bonus/server/`: Dedicated server implementation  
👉 **[See the server protocol documentation here](bonus/server/SERVER.md)**
- `include/`: Header files
- `garbage_collector/`: Memory management system
- `assets/`: Game assets and textures

## Performance

The game includes:
- Network latency display
- Object synchronization statistics
- FPS optimization
- Memory management
- Performance profiling (`make analyse`)

## License

This project is part of EPITECH's curriculum.
