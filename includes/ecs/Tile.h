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
        SDL_Rect* tile_rect;

        Transform* transf;
        Sprite* sprite;

        char* file;
        int id;

        Tile() = default;

        Tile(int x, int y, int w, int h, int id)
        {
            tile_rect = new SDL_Rect();
            tile_rect->x = x;
            tile_rect->y = y;
            tile_rect->w = w;
            tile_rect->h = h;
            this->id = id;

            switch(id)
            {
            case 0:
                file = "../../assets/player_temp.png";
                break;

            case 1:
                file = "../../assets/enemy_temp.png";
                break;

            default: break;
            }
        }

        void Init() override
        {
            entity->AddComponent<Transform>(
                static_cast<float>(tile_rect->x),
                static_cast<float>(tile_rect->y),
                static_cast<float>(tile_rect->w),
                static_cast<float>(tile_rect->h),
                1.0f
            );

            transf = &entity->GetComponent<Transform>();

            entity->AddComponent<Sprite>(file);
            sprite = &entity->GetComponent<Sprite>();
        }
    };
}