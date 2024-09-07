#pragma once

#include <SDL.h>

class Collider;

namespace GAlpha
{
    class Collision
    {
    public:
        static bool BothAABBCollide(
            const SDL_Rect* left, const SDL_Rect* right);

        static bool BothAABBCollide(
            const Collider* left, const Collider* right);
    };
}