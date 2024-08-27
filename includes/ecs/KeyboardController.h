#pragma once

#include "ECS.h"
#include "Components.h"

#include "../Game.h"

namespace GAlpha
{
    class KeyboardController : public Component
    {
    public:
        Transform* transf;

        void Init() override
        {
            transf = &entity->GetComponent<Transform>();
        }

        void Update() override
        {
            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transf->vel.y--;
                    break;

                case SDLK_a:
                    transf->vel.x--;
                    break;

                case SDLK_s:
                    transf->vel.y++;
                    break;

                case SDLK_d:
                    transf->vel.x++;
                    break;

                default: break;
                }
            }

            if (Game::event.type == SDL_KEYUP)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transf->vel.y = 0.0f;
                    break;

                case SDLK_a:
                    transf->vel.x = 0.0f;
                    break;

                case SDLK_s:
                    transf->vel.y = 0.0f;
                    break;

                case SDLK_d:
                    transf->vel.x = 0.0f;
                    break;

                default: break;
                }
            }
        }
    };
}