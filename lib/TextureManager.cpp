#include "TextureManager.h"

using namespace GAlpha;

SDL_Texture* TextureManager::LoadTexture(const char* file)
{
    SDL_Surface* temp_surf = IMG_Load(file);
	if(!temp_surf)
	{
		printf("Surface was not loaded!\n");
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(
		Game::renderer, temp_surf);
		
	SDL_FreeSurface(temp_surf);
	if(!tex)
	{
		printf("Player texture was not created!\n");
		return nullptr;
	}

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst)
{
	SDL_RenderCopy(Game::renderer, tex, src, dst);
}