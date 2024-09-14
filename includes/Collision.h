#pragma once

#include <SDL.h>

namespace GAlpha
{

	class Collider;

	class Collision
	{
	public:
		static bool BothAABBCollide(const SDL_Rect* left, const SDL_Rect* right);
		static bool BothAABBCollide(const Collider* left, const Collider* right);
	};
} // namespace GAlpha