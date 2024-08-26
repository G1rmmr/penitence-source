#pragma once

#include "Game.h"

namespace GAlpha
{
    class TextureManager
    {
    public:
        static SDL_Texture* LoadTexture(const char* file_name);
        static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest);
    };
}