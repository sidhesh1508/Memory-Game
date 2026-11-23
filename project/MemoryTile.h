#include "raylib.h"
#include <string>
#include <vector>

enum MemoryTileStatus {
	Hidden,
	Flipped,
	Matched
};
class MemoryTile
{
public :
	//x,y,w,h
	Rectangle rect;
	int number = 13;
	MemoryTileStatus status = Hidden;
	MemoryTile(float x,float y, float size,int num)
	{
		rect = Rectangle{ x,y,size,size };
		this->number = num;
	}
	
        void Draw(const std::vector<Texture2D>&pictures, bool showPictures)
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
                    rect.x + rect.width / 2 - textWidth / 2,
                    rect.y + rect.height / 2 - fontSize / 2,
                    fontSize,
                    BLACK
                );
            }
            else if (showPictures)
            {
                Texture2D picture = pictures[number - 1];

               
                    

                float maxSize = rect.width - 10;
                float scale = std::min(
                    maxSize / picture.width,
                    maxSize / picture.height
                );

                float drawWidth = picture.width * scale;
                float drawHeight = picture.height * scale;

                Rectangle destination = {
                    rect.x + (rect.width - drawWidth) / 2,
                    rect.y + (rect.height - drawHeight) / 2,
                    drawWidth,
                    drawHeight
                };

                DrawTexturePro(
                    picture,
                    Rectangle{ 0, 0, (float)picture.width, (float)picture.height },
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
                    rect.x + rect.width / 2 - textWidth / 2,
                    rect.y + rect.height / 2 - fontSize / 2,
                    fontSize,
                    BLACK
                );
            }
        }
	
};