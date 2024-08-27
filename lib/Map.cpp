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

	for(int i = 0; i < size_y; ++i)
	{
		for(int j = 0; j < size_x; ++j)
		{
			file.get(tile);
			Game::AddTile(atoi(&tile), i * 32, j * 32);

			file.ignore();
		}
	}
	file.close();
}