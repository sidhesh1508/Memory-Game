#pragma once

#include <vector>
#include "raylib.h"
#include "MemoryTile.h"

class Memory
{
private:
    static constexpr int GAP = 16;
    static constexpr float WAIT_TIME = 0.5f;

    static constexpr int windowWidth = 800;
    static constexpr int windowHeight = 900;
    static constexpr int boardTop = 100;

    Rectangle numbersButton{ 20, 20, 130, 42 };
    Rectangle picturesButton{ 160, 20, 130, 42 };
    Rectangle size2Button{ 340, 20, 90, 42 };
    Rectangle size4Button{ 440, 20, 90, 42 };
    Rectangle size6Button{ 540, 20, 90, 42 };
    Rectangle restartButton{ 660, 20, 120, 42 };

    void DrawButton(Rectangle button, const char* text, bool selected) const;
    void DrawControls() const;
    bool HandleControlClicks();

public:
    bool showPictures = false;
    std::vector<MemoryTile> tiles;
    std::vector<Texture2D> pictures;

    int gridSize = 4;
    MemoryTile* tile1 = nullptr;
    MemoryTile* tile2 = nullptr;
    bool compareMode = false;
    float timeOfSecondClick = -1.0f;

    void Main();
    void Start();
    void Update();
};