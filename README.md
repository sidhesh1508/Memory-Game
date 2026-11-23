# Memory Game

A C++ memory matching game built with Raylib. Choose to play with numbers or pictures, then select a grid size and find all the matching pairs.

## How to Play

1. Choose **Numbers** or **Pictures**.
2. Choose a **2×2**, **4×4**, or **6×6** grid.
3. Click tiles to reveal them and find matching pairs.
4. Match every pair to see the **YOU WIN!** message.

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

The game loads its pictures from `project/resources`. If they don’t load when running from Visual Studio, set the project’s **Working Directory** to `$(ProjectDir)` under **Project Properties → Configuration Properties → Debugging**.

## Picture Assets

The `project/resources` folder should contain `pictures1.png` through `pictures18.png`.

Keep this folder with the project so picture mode can load its images.
