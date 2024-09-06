#include "Map.h"
#include "Game.h"

#include "ecs/ECS.h"
#include "ecs/Components.h"

#include <fstream>

using namespace GAlpha;

extern Manager manager;

Map::Map(const std::string& tex_id, int map_scale, int tile_size)
	: tex_id(tex_id),
	map_scale(map_scale),
	tile_size(tile_size),
	scaled_size(map_scale * tile_size)
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
			src_y = atoi(&tile) * tile_size;

			file.get(tile);
			src_x = atoi(&tile) * tile_size;

			AddTile(src_x, src_y, scaled_size, scaled_size);
			file.ignore();
		}
	}
	file.ignore();

	for(int i = 0; i < size_y; ++i)
	{
		for(int j = 0; j < size_x; ++j)
		{
			file.get(tile);

			if(tile == '1')
			{
				auto& tile_coll(manager.AddEntity());
				tile_coll.AddComponent<Collider>("terrain",
					j * scaled_size, i * scaled_size, scaled_size);
				
				tile_coll.AddGroup(Game::GROUP_COLLIDERS);
			}
			file.ignore();
		}
	}
	file.close();
}

void Map::AddTile(int src_x, int src_y, int x, int y)
{
	auto &tile(manager.AddEntity());
	tile.AddComponent<Tile>(src_x, src_y, x, y, tile_size, map_scale, tex_id);
	tile.AddGroup(Game::GROUP_MAP);
}