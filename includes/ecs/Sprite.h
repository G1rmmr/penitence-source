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
            trans = &entity->GetComponent<Transform>();

            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = trans->width;
            src->h = trans->height;

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
            dst->w = trans->width * trans->scale;
            dst->h = trans->height * trans->scale;
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