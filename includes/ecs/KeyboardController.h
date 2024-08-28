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
        Sprite* sprite;

        void Init() override
        {
            transf = &entity->GetComponent<Transform>();
            sprite = &entity->GetComponent<Sprite>();
        }

        void Update() override
        {
            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transf->vel.y--;
                    sprite->Play("WALK");
                    break;

                case SDLK_a:
                    transf->vel.x--;
                    sprite->Play("WALK");
                    sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
                    break;

                case SDLK_s:
                    transf->vel.y++;
                    sprite->Play("WALK");
                    break;

                case SDLK_d:
                    transf->vel.x++;
                    sprite->Play("WALK");
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
                    sprite->Play("IDLE");
                    break;

                case SDLK_a:
                    transf->vel.x = 0.0f;
                    sprite->Play("IDLE");
                    sprite->sprite_flip = SDL_FLIP_NONE;
                    break;

                case SDLK_s:
                    transf->vel.y = 0.0f;
                    sprite->Play("IDLE");
                    break;

                case SDLK_d:
                    transf->vel.x = 0.0f;
                    sprite->Play("IDLE");
                    break;

                default: break;
                }
            }
        }
    };
}