# Memory Game
## Gameplay

![Memory game gameplay](assets/memorygame.gif)
A C++ memory matching game made with Raylib.

## How to Play

1. Choose **Numbers** or **Pictures**.
2. Choose a **2×2**, **4×4**, or **6×6** grid.
3. Click two tiles to reveal them and find matching pairs.
4. Match every pair to win.

## Controls

- **N** — choose number mode
- **P** — choose picture mode
- **1** — choose a 2×2 grid
- **2** — choose a 4×4 grid
- **3** — choose a 6×6 grid
- **Left mouse button** — flip a tile

## Requirements

- Visual Studio with a C++ compiler
- Raylib installed and configured for the project

## Run the Game

Open `Saturday.slnx` in Visual Studio and run the project.

The game loads picture assets from `project/resources`. If the pictures don’t load, set the project’s **Working Directory** to `$(ProjectDir)` under **Project Properties → Configuration Properties → Debugging**.

## Project Structure

    Saturday/
    ├── .gitignore
    ├── README.md
    ├── Saturday.slnx
    └── project/
        ├── Memory.cpp
        ├── Memory.h
        ├── MemoryTile.cpp
        ├── MemoryTile.h
        ├── main.cpp
        ├── project.vcxproj
        ├── project.vcxproj.filters
        └── resources/
            ├── pictures1.png
            ├── pictures2.png
            ├── ...
            └── pictures18.png
