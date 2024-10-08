#include "Collision.h"

#include "ecs/Collider.h"

using namespace GAlpha;

bool Collision::BothAABBCollide(
	const SDL_Rect* left, const SDL_Rect* right)
{
	if(left->x + left->w < right->x) return false;
	if(left->y + left->h < right->y) return false;
	if(right->x + right->w < left->x) return false;
	if(right->y + right->h < left->y) return false;

	return true;
}

inline bool Collision::BothAABBCollide(
	const Collider* left, const Collider* right)
{
	return BothAABBCollide(left->collider, right->collider);
}