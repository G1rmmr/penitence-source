#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Transform.h"
#include "Sprite.h"

namespace GAlpha
{
    class Tile : public Component
    {
    public:
        SDL_Texture* tex;
        SDL_Rect* src;
        SDL_Rect* dst;

        Tile() = default;

        ~Tile()
        {
            SDL_DestroyTexture(tex);
        }

        Tile(const char* path, int src_x, int src_y, int x, int y)
        {
            tex = TextureManager::Load(path);

            src = new SDL_Rect();
            src->x = src_x;
            src->y = src_y;
            src->w = 32;
            src->h = 32;

            dst = new SDL_Rect();
            dst->x = x;
            dst->y = y;
            dst->w = 32;
            dst->h = 32;
        }
    };
}