#include "GameObject.h"
#include "TextureManager.h"

using namespace GAlpha;

const int PNG_SIZE = 150;

GameObject::GameObject(const char* tex_sheet, int x, int y) :
    obj_tex(),
    obj_renderer(),
    src_rect(nullptr),
    dst_rect(nullptr),
    pos(std::make_pair(x, y))
{
    obj_tex = TextureManager::Load(tex_sheet);
    obj_renderer = Game::renderer;

    src_rect = new SDL_Rect();
    src_rect->x = 0;
    src_rect->y = 0;
    src_rect->w = PNG_SIZE;
    src_rect->h = PNG_SIZE;

    dst_rect = new SDL_Rect();
    dst_rect->x = 0;
    dst_rect->y = 0;
    dst_rect->w = 0;
    dst_rect->h = 0;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
    ++pos.first;
    ++pos.second;

    dst_rect->x = pos.first;
    dst_rect->y = pos.second;
    dst_rect->w = src_rect->w * 2;
    dst_rect->h = src_rect->h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, obj_tex, src_rect, dst_rect);
}