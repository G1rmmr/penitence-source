#pragma once

#include "Game.h"

#include <utility>

namespace GAlpha
{
    class GameObject
    {
    public:
        GameObject(const char* tex_sheet, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:
        SDL_Texture* obj_tex;
        SDL_Renderer* obj_renderer;

        SDL_Rect* src_rect;
        SDL_Rect* dst_rect;

        std::pair<int, int> pos;
    };
}