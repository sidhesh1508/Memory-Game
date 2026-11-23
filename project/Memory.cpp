#include "Memory.h"
#include "raylib.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void Memory::Main()
{
	InitWindow(widthHeight, widthHeight, "Memory");
	SetTargetFPS(60);

	int menuStage = 0;
	for (int i = 1; i <= 18; i++)
	{
		string path = "resources/pictures" + to_string(i) + ".png";
		Texture2D picture = LoadTexture(path.c_str());

		if (picture.id == 0)
			TraceLog(LOG_ERROR, "Could not load: %s", path.c_str());

		pictures.push_back(picture);
	}
	while (!WindowShouldClose())
	{
		if (menuStage == 0)
		{
			if (IsKeyPressed(KEY_N))
			{
				showPictures = false;
				menuStage = 1;
			}
			else if (IsKeyPressed(KEY_P))
			{
				showPictures = true;
				menuStage = 1;
			}
		}
		else if (menuStage == 1)
		{
			if (IsKeyPressed(KEY_ONE))
			{
				gridSize = 2;
				Start();
				menuStage = 2;
			}
			else if (IsKeyPressed(KEY_TWO))
			{
				gridSize = 4;
				Start();
				menuStage = 2;
			}
			else if (IsKeyPressed(KEY_THREE))
			{
				gridSize = 6;
				Start();
				menuStage = 2;
			}
		}

		BeginDrawing();
		ClearBackground(GRAY);

		if (menuStage == 0)
		{
			DrawText("Choose how to play", 250, 250, 32, BLACK);
			DrawText("Press N for numbers", 280, 320, 24, BLACK);
			DrawText("Press P for pictures", 280, 360, 24, BLACK);
		}
		else if (menuStage == 1)
		{
			DrawText("Choose your grid size", 240, 250, 32, BLACK);
			DrawText("Press 1 for 2x2", 300, 320, 24, BLACK);
			DrawText("Press 2 for 4x4", 300, 360, 24, BLACK);
			DrawText("Press 3 for 6x6", 300, 400, 24, BLACK);
		}
		else
		{
			Update();
		}

		EndDrawing();
	}
	for (Texture2D picture : pictures)
	{
		UnloadTexture(picture);
	}
	CloseWindow();
}

void Memory::Start()
{
	
		tiles.clear();
		tile1 = nullptr;
		tile2 = nullptr;
		compareMode = false;
		timeOfSecondClick = -1.0f;


		// Keep the rest of your existing Start() code here.
	int x = GAP;
	int y = GAP;

	int widthForTiles = widthHeight - (gridSize + 1) * GAP;
	int size = widthForTiles / gridSize;


	static std::mt19937 rng(std::random_device{}());

	std::vector<int> pictureIds;
	for (int i = 1; i <= static_cast<int>(pictures.size()); i++)
	{
		pictureIds.push_back(i);
	}
	std::shuffle(pictureIds.begin(), pictureIds.end(), rng);

	std::vector<int> numbers;
	int pairCount = gridSize * gridSize / 2;

	for (int i = 0; i < pairCount; i++)
	{
		int id = showPictures ? pictureIds[i] : i + 1;
		numbers.push_back(id);
		numbers.push_back(id);
	}

	std::shuffle(numbers.begin(), numbers.end(), rng);


	// 1,1, 2,2 3,3, 4,4, 5,5, 6,6, 7,7, 8,8
	int numberIndex = 0;

	for (int c = 0; c < gridSize; c++)
	{
		for (int r = 0; r < gridSize; r++)
		{
			int n = numbers[numberIndex++];

			MemoryTile tile(x, y, size, n);
			tiles.push_back(tile);

			x += GAP + size;
		}

		y += GAP + size;
		x = GAP;
	}
}

void Memory::Update()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !compareMode)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), tiles[i].rect))
			{
				if (tiles[i].status != Hidden)break;
				{

				}
					tiles[i].status = Flipped;
					if (tile1 == nullptr)//so there is no tile one just yet 
					{
						tile1 = &tiles[i];//this was the first click

					}
					else //there 's been a click before, this is the second tile
					{
						tile2 = &tiles[i];
						compareMode = true;
						timeOfSecondClick = GetTime();//register it was now that we clicked second time

					}
					break;//because if we landed on a tile, there is no way, we woudl land on another
				
			}
		}
	}
	if (tile2!=nullptr)// means we should compare
	{
		//now, let's compare them
		if (GetTime() > timeOfSecondClick + WAIT_TIME)
		{

			if (tile1->number == tile2->number)
			{
				tile1->status = tile2->status = Matched;
			}
			else
			{
				tile1->status = tile2->status = Hidden;
			}
			tile1 = tile2 = nullptr;
			compareMode = false;
		}
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

	for (MemoryTile& tile : tiles)
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
			(widthHeight - textWidth) / 2,
			(widthHeight - fontSize) / 2,
			fontSize,
			RED
		);
	}
}