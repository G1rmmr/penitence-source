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

        Vector2D pos;

        Tile() = default;

        ~Tile()
        {
            SDL_DestroyTexture(tex);
        }

        Tile(const char* path, int src_x, int src_y, int x, int y)
        {
            tex = TextureManager::Load(path);

            pos.x = x;
            pos.y = y;

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

        void Update() override
        {
            dst->x = pos.x - Game::camera->x;
            dst->y = pos.y - Game::camera->y;
        }

        void Draw() override
        {
            TextureManager::Draw(tex, src, dst, SDL_FLIP_NONE);
        }
    };
}