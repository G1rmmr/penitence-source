#pragma once

#include <SDL.h>

namespace GAlpha
{
    class Collision
    {
    public:
        static bool BothAABBCollide(
            const SDL_Rect& left, const SDL_Rect& right);
    };
}