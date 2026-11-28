#pragma once

#include "raylib.h"
#include <algorithm>
#include <string>
#include <vector>

enum MemoryTileStatus
{
    Hidden,
    Flipped,
    Matched
};

class MemoryTile
{
public:
    Rectangle rect{};
    int number = 0;
    MemoryTileStatus status = Hidden;

    MemoryTile(float x, float y, float size, int num)
    {
        rect = Rectangle{ x, y, size, size };
        number = num;
    }

    void Draw(const std::vector<Texture2D>& pictures, bool showPictures) const
    {
        Color tileColor = status == Matched ? GREEN :
            status == Flipped ? WHITE : ORANGE;

        DrawRectangleRounded(rect, 0.25f, 12, tileColor);

        if (status == Hidden)
        {
            const char* text = "?";
            int fontSize = 40;
            int textWidth = MeasureText(text, fontSize);

            DrawText(
                text,
                static_cast<int>(rect.x + rect.width / 2 - textWidth / 2),
                static_cast<int>(rect.y + rect.height / 2 - fontSize / 2),
                fontSize,
                BLACK
            );
        }
        else if (showPictures)
        {
            if (number < 1 ||
                number > static_cast<int>(pictures.size()) ||
                pictures[number - 1].id == 0)
            {
                DrawText("Missing image",
                    static_cast<int>(rect.x + 8),
                    static_cast<int>(rect.y + rect.height / 2),
                    18,
                    RED);
                return;
            }

            Texture2D picture = pictures[number - 1];

            float maxSize = rect.width - 10;
            float scale = std::min(
                maxSize / picture.width,
                maxSize / picture.height
            );

            float drawWidth = picture.width * scale;
            float drawHeight = picture.height * scale;

            Rectangle destination{
                rect.x + (rect.width - drawWidth) / 2,
                rect.y + (rect.height - drawHeight) / 2,
                drawWidth,
                drawHeight
            };

            DrawTexturePro(
                picture,
                Rectangle{ 0, 0,
                    static_cast<float>(picture.width),
                    static_cast<float>(picture.height) },
                destination,
                Vector2{ 0, 0 },
                0.0f,
                WHITE
            );
        }
        else
        {
            std::string text = std::to_string(number);
            int fontSize = 40;
            int textWidth = MeasureText(text.c_str(), fontSize);

            DrawText(
                text.c_str(),
                static_cast<int>(rect.x + rect.width / 2 - textWidth / 2),
                static_cast<int>(rect.y + rect.height / 2 - fontSize / 2),
                fontSize,
                BLACK
            );
        }
    }
};