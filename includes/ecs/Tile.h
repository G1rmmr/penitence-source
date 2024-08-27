#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Transform.h"
#include "Sprite.h"

namespace GAlpha
{
    class Tile : public Component
    {
    public:
        SDL_Rect* tile;

        Transform* transf;
        Sprite* sprite;

        char* path;
        int id;

        Tile() = default;

        Tile(int x, int y, int w, int h, int id)
        {
            tile = new SDL_Rect();
            tile->x = x;
            tile->y = y;
            tile->w = w;
            tile->h = h;
            this->id = id;

            switch(id)
            {
            case 0:
                path = "../../assets/player_temp.png";
                break;

            case 1:
                path = "../../assets/enemy_temp.png";
                break;

            default: break;
            }
        }

        void Init() override
        {
            entity->AddComponent<Transform>(
                static_cast<float>(tile->x),
                static_cast<float>(tile->y),
                static_cast<float>(tile->w),
                static_cast<float>(tile->h),
                1.0f
            );

            transf = &entity->GetComponent<Transform>();

            entity->AddComponent<Sprite>(path);
            sprite = &entity->GetComponent<Sprite>();
        }
    };
}