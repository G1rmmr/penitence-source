#include "GameObject.h"
#include "TextureManager.h"

using namespace GAlpha;

const int IMG_SIZE = 150;

GameObject::GameObject(const char* path, int x, int y) :
    tex(), renderer(), src(nullptr), dst(nullptr), pos(std::make_pair(x, y))
{
    tex = TextureManager::Load(path);
    renderer = Game::renderer;

    src = new SDL_Rect();
    src->x = 0;
    src->y = 0;
    src->w = IMG_SIZE;
    src->h = IMG_SIZE;

    dst = new SDL_Rect();
    dst->x = 0;
    dst->y = 0;
    dst->w = 0;
    dst->h = 0;
}

GameObject::~GameObject()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);

    delete src;
    delete dst;
}

void GameObject::Update()
{
    ++pos.first;
    ++pos.second;

    dst->x = pos.first;
    dst->y = pos.second;
    dst->w = src->w * 2;
    dst->h = src->h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, tex, src, dst);
}