#pragma once

#include <SDL.h>

#include "Components.h"
#include "../TextureManager.h"

namespace GAlpha
{
    class Sprite : public Component
    {
    public:
        Sprite() = default;

        Sprite(const char* path)
        {
            SetTexture(path);
        }

        ~Sprite()
        {
            SDL_DestroyTexture(tex);
        }

        void SetTexture(const char* path)
        {
            tex = TextureManager::LoadTexture(path);
        }

        void Init() override
        {
            transf = &entity->GetComponent<Transform>();

            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = transf->width;
            src->h = transf->height;

            dst = new SDL_Rect();
            dst->x = 0;
            dst->y = 0;
            dst->w = 0;
            dst->h = 0;
        }

        void Update() override
        {
            dst->x = static_cast<int>(transf->pos.x);
            dst->y = static_cast<int>(transf->pos.y);
            dst->w = transf->width * transf->scale;
            dst->h = transf->height * transf->scale;
        }

        void Draw() override
        {
            TextureManager::Draw(tex, src, dst);
        }

    private:
        SDL_Texture* tex;
        SDL_Rect* src;
        SDL_Rect* dst;

        Transform* transf;
    };
}