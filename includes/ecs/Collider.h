#pragma once

#include <SDL.h>

#include <string>

#include "Components.h"
#include "../TextureManager.h"

namespace GAlpha
{
    class Collider : public Component
    {
    public:
        SDL_Rect* collider;
        std::string tag;

        SDL_Texture* tex;
        SDL_Rect* src;
        SDL_Rect* dst;

        Transform* transf;

        Collider(const std::string& tag) : tag(tag)
        {
            
        }

        void Init() override
        {
            if(!entity->HasComponent<Transform>())
                entity->AddComponent<Transform>();

            transf = &entity->GetComponent<Transform>();

            tex = TextureManager::Load("");
            
            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = 32;
            src->h = 32;

            dst->x = collider->x;
            dst->y = collider->y;
            dst->w = collider->w;
            dst->h = collider->h;

            Game::colliders.emplace_back(this);
        }

        void Update() override
        {
            if(tag != "terrain")
            {
                collider->x = static_cast<int>(transf->pos.x);
                collider->y = static_cast<int>(transf->pos.y);
                collider->w = transf->width * transf->scale;
                collider->h = transf->height * transf->scale;
            }
            

            dst->x = collider->x - Game::camera->x;
            dst->y = collider->y - Game::camera->y; 
        }

        void Draw() override
        {
            TextureManager::Draw(tex, src, dst, SDL_FLIP_NONE);
        }
    };
}