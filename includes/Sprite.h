#pragma once

#include <SDL.h>

#include "Components.h"

namespace GAlpha
{
    class Sprite : public Component
    {
    public:
        Sprite() = default;

        Sprite(const char* path)
        {
            tex = TextureManager::LoadTexture(path);
        }

        void SetTexture(const char* path)
        {
            tex = TextureManager::LoadTexture(path);
        }

        void Init() override
        {
            trans = &entity->GetComponent<Transform>();

            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = 150;
            src->h = 150;

            dst = new SDL_Rect();
            dst->x = 0;
            dst->y = 0;
            dst->w = 0;
            dst->h = 0;
        }

        void Update() override
        {
            dst->x = static_cast<int>(trans->pos.x);
            dst->y = static_cast<int>(trans->pos.y);
            dst->w = static_cast<int>(src->w * 2);
            dst->h = static_cast<int>(src->h * 2);
        }

        void Draw() override
        {
            TextureManager::Draw(tex, src, dst);
        }

    private:
        SDL_Texture* tex;
        SDL_Rect* src;
        SDL_Rect* dst;

        Transform* trans;
    };
}