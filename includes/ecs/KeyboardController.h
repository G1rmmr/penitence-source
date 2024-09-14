#pragma once

#include "../Game.h"

#include "ECS.h"
#include "Components.h"

namespace GAlpha
{
	class KeyboardController : public Component
	{
	public:
		Transform* transf = new Transform();
		Sprite* sprite = new Sprite();

		KeyboardController()
		{
		}

		~KeyboardController()
		{
		}

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
					transf->vel.y = -1;
					sprite->Play("MOVE");
					break;

				case SDLK_a:
					transf->vel.x = -1;
					sprite->Play("MOVE");
					sprite->flip = SDL_FLIP_HORIZONTAL;
					break;

				case SDLK_s:
					transf->vel.y = 1;
					sprite->Play("MOVE");
					break;

				case SDLK_d:
					transf->vel.x = 1;
					sprite->Play("MOVE");
					break;

				case SDLK_SPACE:
					sprite->Play("JUMP");
					break;

				case SDLK_ESCAPE:
					Game::is_running = false;
					break;

				default:
					break;
				}
			}

			if(Game::event.type == SDL_KEYUP)
			{
				switch(Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transf->vel.y = 0.0f;
					sprite->Play("IDLE");
					break;

				case SDLK_a:
					transf->vel.x = 0.0f;
					sprite->Play("IDLE");
					sprite->flip = SDL_FLIP_NONE;
					break;

				case SDLK_s:
					transf->vel.y = 0.0f;
					sprite->Play("IDLE");
					break;

				case SDLK_d:
					transf->vel.x = 0.0f;
					sprite->Play("IDLE");
					break;

				case SDLK_SPACE:
					sprite->Play("IDLE");
					break;

				case SDLK_ESCAPE:
					Game::is_running = false;
					break;

				default:
					break;
				}
			}
		}
	};
} // namespace GAlpha