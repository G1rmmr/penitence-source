#pragma once

#include <unordered_map>
#include <cstdio>

#include <SDL.h>

#include "Animation.h"
#include "Components.h"

#include "../AssetManager.h"
#include "../TextureManager.h"

namespace GAlpha
{
	class Sprite : public Component
	{
	public:
		std::unordered_map<const char*, Animation> anims;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		int anim_index = 0;

		Sprite() = default;

		Sprite(const std::string& id)
		{
			SetTexture(id);
		}

		Sprite(const std::string& id, bool is_anim) : is_anim(is_anim)
		{
			anims.emplace("IDLE", Animation(0, 3, 100));
			anims.emplace("MOVE", Animation(1, 6, 100));
			anims.emplace("JUMP", Animation(2, 6, 100));

			Play("IDLE");
			SetTexture(id);
		}

		~Sprite()
		{
			SDL_DestroyTexture(tex);
		}

		void Init() override
		{
			transf = &entity->GetComponent<Transform>();

			src->x = 0;
			src->y = 0;
			src->w = static_cast<int>(transf->width);
			src->h = static_cast<int>(transf->height);

			dst->x = 0;
			dst->y = 0;
			dst->w = 0;
			dst->h = 0;
		}

		void Update() override
		{
			if(is_anim)
				src->x = src->w * static_cast<int>(
					(SDL_GetTicks() / speed) % frames);

			src->y = static_cast<int>(anim_index * transf->height);

			dst->x = static_cast<int>(transf->pos.x - Game::camera->x);
			dst->y = static_cast<int>(transf->pos.y - Game::camera->y);
			dst->w = static_cast<int>(transf->width * transf->scale);
			dst->h = static_cast<int>(transf->height * transf->scale);
		}

		void Draw() override
		{
			TextureManager::Draw(tex, src, dst, flip);
		}

		inline void SetTexture(const std::string& id)
		{
			tex = Game::assets->GetTexture(id);
		}

		void Play(const char* anim_name)
		{
			auto anim = anims[anim_name];

			frames = anim.frames;
			anim_index = anim.index;
			speed = anim.speed;
		}

	private:
		SDL_Texture* tex = nullptr;
		SDL_Rect* src = new SDL_Rect();
		SDL_Rect* dst = new SDL_Rect();

		Transform* transf = new Transform();

		int frames = 30;
		int speed = 100;

		bool is_anim = false;
	};
} // namespace GAlpha