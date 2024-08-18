#pragma once

#include "Game.h"

namespace GAlpha
{
    class TextureManager
    {
    public:
        static SDL_Texture* LoadTexture(const char* file_name, SDL_Renderer* renderer);
    };
}