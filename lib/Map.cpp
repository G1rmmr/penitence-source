#include "Map.h"
#include "Game.h"

#include <fstream>

using namespace GAlpha;

Map::Map()
{

}

Map::~Map()
{

}

void Map::Load(const char* path, int size_x, int size_y)
{	
	char tile;
	std::fstream file;
	file.open(path);

	int src_x;
	int src_y;

	for(int i = 0; i < size_y; ++i)
	{
		for(int j = 0; j < size_x; ++j)
		{
			file.get(tile);
			src_y = atoi(&tile) * 32;

			file.get(tile);
			src_x = atoi(&tile) * 32;

			Game::AddTile(src_x, src_y, size_x * 32, size_y * 32);
			file.ignore();
		}
	}
	file.close();
}