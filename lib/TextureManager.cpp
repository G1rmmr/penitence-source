#include "TextureManager.h"

using namespace GAlpha;

SDL_Texture *TextureManager::Load(const char *path)
{
    SDL_Surface *surf = IMG_Load(path);
    if (!surf)
    {
        printf("Surface was not loaded!\n");
        return nullptr;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);

    if (!tex)
    {
        printf("Player texture was not created!\n");
        return nullptr;
    }

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, src, dst, 0.0, nullptr, flip);
}