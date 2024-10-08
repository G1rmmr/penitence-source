#pragma once

#include <string>

namespace GAlpha
{
class Map
{
public:
    Map(const std::string& id, int scale, int tile_size);
    ~Map();

    void Load(const char* path, int size_x, int size_y);
    void AddTile(int src_x, int src_y, int x, int y);

  private:
    std::string id;

    int scale = 0;
    int tile_size = 0;
    int scaled_size = 0;
};
} // namespace GAlpha