#include <vector>
#include "raylib.h"
#include "MemoryTile.h"
using namespace std;
class Memory
{
public:
#define WAIT_TIME 0.5
#define GAP 16//arbitererary
	bool showPictures = false;
	vector<MemoryTile> tiles;
	vector<Texture2D> pictures;
	int widthHeight = 800;
	int gridSize = 4;
	MemoryTile* tile1 = nullptr;
	MemoryTile* tile2 = nullptr;
	bool compareMode = false;
	float timeOfSecondClick = -1.0f;//this is when the second click landed
	void Main();//the raylib stuf
	void Start();
	void Update();
};