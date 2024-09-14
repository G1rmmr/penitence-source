#pragma once

#include "ECS.h"
#include "Sprite.h"
#include "Transform.h"

namespace GAlpha
{
	class Tile : public Component
	{
	public:
		SDL_Texture* tex = nullptr;
		SDL_Rect* src = new SDL_Rect();
		SDL_Rect* dst = new SDL_Rect();

		Vector2D pos;

		Tile() = default;

		~Tile()
		{
			SDL_DestroyTexture(tex);
		}

		Tile(const std::string& id,
			int tile_size, int tile_scale,
			int src_x, int src_y, int x, int y)
		{
			tex = Game::assets->GetTexture(id);

			pos.x = static_cast<float>(x);
			pos.y = static_cast<float>(y);

			src->x = src_x;
			src->y = src_y;
			src->w = tile_size;
			src->h = tile_size;

			dst->x = x;
			dst->y = y;
			dst->w = tile_size * tile_scale;
			dst->h = tile_size * tile_scale;
		}

		void Update() override
		{
			dst->x = static_cast<int>(pos.x - Game::camera->x);
			dst->y = static_cast<int>(pos.y - Game::camera->y);
		}

		void Draw() override
		{
			TextureManager::Draw(tex, src, dst, SDL_FLIP_NONE);
		}
	};
} // namespace GAlpha