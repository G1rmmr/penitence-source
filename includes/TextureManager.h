#pragma once

#include "Game.h"

namespace GAlpha
{
class TextureManager
{
  public:
    static SDL_Texture *Load(const char *path);

    static void Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst, SDL_RendererFlip flip);
};
} // namespace GAlpha