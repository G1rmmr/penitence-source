#pragma once

#include "ECS.h"
#include "Components.h"

#include "../Game.h"

namespace GAlpha
{
    class KeyboardController : public Component
    {
    public:
        Transform* transform;

        void Init() override
        {
            transform = &entity->GetComponent<Transform>();
        }

        void Update() override
        {
            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transform->vel.y--;
                    break;

                case SDLK_a:
                    transform->vel.x--;
                    break;

                case SDLK_s:
                    transform->vel.y++;
                    break;

                case SDLK_d:
                    transform->vel.x++;
                    break;

                default: break;
                }
            }

            if (Game::event.type == SDL_KEYUP)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transform->vel.y = 0.0f;
                    break;

                case SDLK_a:
                    transform->vel.x = 0.0f;
                    break;

                case SDLK_s:
                    transform->vel.y = 0.0f;
                    break;

                case SDLK_d:
                    transform->vel.x = 0.0f;
                    break;

                default:
                    break;
                }
            }
        }
    };
}