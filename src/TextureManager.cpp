#include "TextureManager.h"

using namespace GAlpha;

SDL_Texture* TextureManager::LoadTexture(const char* file_name, SDL_Renderer* renderer)
{
    SDL_Surface* temp_surf = IMG_Load(file_name);
	if(!temp_surf)
	{
		printf("Surface was not loaded!\n");
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp_surf);
	SDL_FreeSurface(temp_surf);
	if(!tex)
	{
		printf("Player texture was not created!\n");
		return nullptr;
	}

    return tex;
}