#include "Memory.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

void Memory::Main()
{
    InitWindow(800, 900, "Memory Game");
    SetTargetFPS(60);

    pictures.reserve(18);

    for (int i = 1; i <= 18; ++i)
    {
        std::string path =
            "resources/pictures" + std::to_string(i) + ".png";

        Texture2D picture = LoadTexture(path.c_str());

        if (picture.id == 0)
        {
            TraceLog(LOG_ERROR, "Could not load: %s", path.c_str());
        }

        pictures.push_back(picture);
    }

    Start();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        Update();

        EndDrawing();
    }

    for (Texture2D picture : pictures)
    {
        if (picture.id != 0)
        {
            UnloadTexture(picture);
        }
    }

    CloseWindow();
}

void Memory::Start()
{
    tile1 = nullptr;
    tile2 = nullptr;
    compareMode = false;
    timeOfSecondClick = -1.0f;

    tiles.clear();

    int widthForTiles = 800 - (gridSize + 1) * GAP;
    int tileSize = widthForTiles / gridSize;

    static std::mt19937 rng(std::random_device{}());

    std::vector<int> values;
    int pairCount = gridSize * gridSize / 2;

    if (showPictures)
    {
        std::vector<int> pictureIds;

        for (int i = 1; i <= static_cast<int>(pictures.size()); ++i)
        {
            pictureIds.push_back(i);
        }

        std::shuffle(pictureIds.begin(), pictureIds.end(), rng);

        for (int i = 0; i < pairCount; ++i)
        {
            int id = pictureIds[i];
            values.push_back(id);
            values.push_back(id);
        }
    }
    else
    {
        for (int i = 1; i <= pairCount; ++i)
        {
            values.push_back(i);
            values.push_back(i);
        }
    }

    std::shuffle(values.begin(), values.end(), rng);

    int x = GAP;
    int y = boardTop;
    int valueIndex = 0;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int column = 0; column < gridSize; ++column)
        {
            MemoryTile tile(
                static_cast<float>(x),
                static_cast<float>(y),
                static_cast<float>(tileSize),
                values[valueIndex++]
            );

            tiles.push_back(tile);
            x += GAP + tileSize;
        }

        y += GAP + tileSize;
        x = GAP;
    }
}

void Memory::DrawButton(
    Rectangle button,
    const char* text,
    bool selected
) const
{
    Color fillColor = selected ? SKYBLUE : RAYWHITE;

    DrawRectangleRec(button, fillColor);
    DrawRectangleLinesEx(button, 2, DARKGRAY);

    int fontSize = 18;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        static_cast<int>(button.x + button.width / 2 - textWidth / 2),
        static_cast<int>(button.y + button.height / 2 - fontSize / 2),
        fontSize,
        BLACK
    );
}

void Memory::DrawControls() const
{
    DrawButton(numbersButton, "Numbers", !showPictures);
    DrawButton(picturesButton, "Pictures", showPictures);

    DrawButton(size2Button, "2 x 2", gridSize == 2);
    DrawButton(size4Button, "4 x 4", gridSize == 4);
    DrawButton(size6Button, "6 x 6", gridSize == 6);

    DrawButton(restartButton, "Restart", false);

    DrawText("Choose mode and grid size. Click Restart to reshuffle.",
        20, 70, 18, DARKGRAY);
}

bool Memory::HandleControlClicks()
{
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return false;
    }

    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, numbersButton))
    {
        showPictures = false;
        Start();
        return true;
    }

    if (CheckCollisionPointRec(mousePosition, picturesButton))
    {
        showPictures = true;
        Start();
        return true;
    }

    if (CheckCollisionPointRec(mousePosition, size2Button))
    {
        gridSize = 2;
        Start();
        return true;
    }

    if (CheckCollisionPointRec(mousePosition, size4Button))
    {
        gridSize = 4;
        Start();
        return true;
    }

    if (CheckCollisionPointRec(mousePosition, size6Button))
    {
        gridSize = 6;
        Start();
        return true;
    }

    if (CheckCollisionPointRec(mousePosition, restartButton))
    {
        Start();
        return true;
    }

    return false;
}

void Memory::Update()
{
    bool clickedControl = HandleControlClicks();

    if (!clickedControl &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        !compareMode)
    {
        Vector2 mousePosition = GetMousePosition();

        for (std::size_t i = 0; i < tiles.size(); ++i)
        {
            if (CheckCollisionPointRec(mousePosition, tiles[i].rect))
            {
                if (tiles[i].status == Hidden)
                {
                    tiles[i].status = Flipped;

                    if (tile1 == nullptr)
                    {
                        tile1 = &tiles[i];
                    }
                    else
                    {
                        tile2 = &tiles[i];
                        compareMode = true;
                        timeOfSecondClick = static_cast<float>(GetTime());
                    }
                }

                break;
            }
        }
    }

    if (tile1 != nullptr &&
        tile2 != nullptr &&
        GetTime() >= timeOfSecondClick + WAIT_TIME)
    {
        if (tile1->number == tile2->number)
        {
            tile1->status = Matched;
            tile2->status = Matched;
        }
        else
        {
            tile1->status = Hidden;
            tile2->status = Hidden;
        }

        tile1 = nullptr;
        tile2 = nullptr;
        compareMode = false;
    }

    bool allMatched = !tiles.empty();

    for (const MemoryTile& tile : tiles)
    {
        if (tile.status != Matched)
        {
            allMatched = false;
            break;
        }
    }

    DrawControls();

    for (const MemoryTile& tile : tiles)
    {
        tile.Draw(pictures, showPictures);
    }

    if (allMatched)
    {
        const char* message = "YOU WIN!";
        int fontSize = 60;
        int textWidth = MeasureText(message, fontSize);

        DrawText(
            message,
            (800 - textWidth) / 2,
            450,
            fontSize,
            RED
        );
    }
}