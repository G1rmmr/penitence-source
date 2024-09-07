#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Sprite.h"
#include "Transform.h"

namespace GAlpha
{
class Tile : public Component
{
  public:
    SDL_Texture *tex;
    SDL_Rect src;
    SDL_Rect dst;

    Vector2D pos;

    Tile() = default;

    ~Tile()
    {
        SDL_DestroyTexture(tex);
    }

    Tile(const std::string &id, int tile_size, int tile_scale, int src_x, int src_y, int x, int y)
    {
        tex = Game::assets.GetTexture(id);

        pos.x = x;
        pos.y = y;

        src = SDL_Rect(src_x, src_y, tile_size, tile_size);

        dst = SDL_Rect(x, y, tile_size * tile_scale, tile_size * tile_scale);
    }

    void Update() override
    {
        dst.x = pos.x - Game::camera.x;
        dst.y = pos.y - Game::camera.y;
    }

    void Draw() override
    {
        TextureManager::Draw(tex, &src, &dst, SDL_FLIP_NONE);
    }
};
} // namespace GAlpha