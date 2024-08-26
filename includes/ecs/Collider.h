#pragma once

#include <SDL.h>

#include <string>

#include "Components.h"

namespace GAlpha
{
    class Collider : public Component
    {
    public:
        SDL_Rect* collider;
        std::string tag;

        Transform* transf;

        Collider(const std::string& tag) : tag(tag)
        {
            collider = new SDL_Rect();
        }

        void Init() override
        {
            if(!entity->HasComponent<Transform>())
                entity->AddComponent<Transform>();

            transf = &entity->GetComponent<Transform>();
        }

        void Update() override
        {
            collider->x = static_cast<int>(transf->pos.x);
            collider->y = static_cast<int>(transf->pos.y);
            collider->w = transf->width * transf->scale;
            collider->h = transf->height * transf->scale;
        }
    };
}