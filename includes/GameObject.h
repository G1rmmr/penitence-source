#pragma once

#include <utility>

#include "Game.h"

namespace GAlpha
{
class GameObject
{
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:
    SDL_Texture* tex;
    SDL_Renderer* renderer;

    SDL_Rect* src;
    SDL_Rect* dst;

    std::pair<int, int> pos;
};
} // namespace GAlpha