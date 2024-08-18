#include "GameObject.h"
#include "TextureManager.h"

using namespace GAlpha;

const int PNG_SIZE = 150;

GameObject::GameObject(const char* tex_sheet, SDL_Renderer* renderer, int x, int y) :
    obj_tex(), obj_renderer(renderer), src_rect(nullptr), dest_rect(nullptr), pos(std::make_pair(x, y))
{
    obj_tex = TextureManager::LoadTexture(tex_sheet, renderer);

    src_rect = new SDL_Rect();
    src_rect->x = 0;
    src_rect->y = 0;
    src_rect->w = PNG_SIZE;
    src_rect->h = PNG_SIZE;

    dest_rect = new SDL_Rect();
    dest_rect->x = 0;
    dest_rect->y = 0;
    dest_rect->w = 0;
    dest_rect->h = 0;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
    ++pos.first;
    ++pos.second;

    dest_rect->x = pos.first;
    dest_rect->y = pos.second;
    dest_rect->w = src_rect->w * 2;
    dest_rect->h = src_rect->h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(obj_renderer, obj_tex, src_rect, dest_rect);
}