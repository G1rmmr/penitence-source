#include <fstream>

#include "ecs/Components.h"
#include "ecs/ECS.h"

#include "Game.h"
#include "Map.h"

using namespace GAlpha;

extern Manager* manager;

Map::Map(const std::string& id, int scale, int tile_size)
    : id(id), scale(scale), tile_size(tile_size),
    scaled_size(scale * tile_size)
{
}

Map::~Map()
{
}

void Map::Load(const char *path, int size_x, int size_y)
{
    char tile;
    std::fstream file;
    file.open(path);

    int src_x;
    int src_y;

    for (int i = 0; i < size_y; ++i)
    {
        for (int j = 0; j < size_x; ++j)
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

    for (int i = 0; i < size_y; ++i)
    {
        for (int j = 0; j < size_x; ++j)
        {
            file.get(tile);

            if (tile == '1')
            {
                auto &coll(manager->AddEntity());
                
                coll.AddComponent<Collider>(
                    "terrain", j * scaled_size, i * scaled_size, scaled_size);

                coll.AddGroup(Game::GROUP_COLLIDERS);
            }
            file.ignore();
        }
    }
    file.close();
}

void Map::AddTile(int src_x, int src_y, int x, int y)
{
    auto& tile(manager->AddEntity());
    tile.AddComponent<Tile>(id, tile_size, scale, src_x, src_y, x, y);
    tile.AddGroup(Game::GROUP_MAP);
}