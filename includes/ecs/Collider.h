#pragma once

#include <string>

#include <SDL.h>

#include "Components.h"

#include "../TextureManager.h"

namespace GAlpha
{
class Collider : public Component
{
public:
    SDL_Rect* collider;
    SDL_Rect* src;
    SDL_Rect* dst;

    SDL_Texture* tex;

    std::string tag;

    Transform* transf;

    Collider(const std::string& tag) : tag(tag)
    {
        collider = new SDL_Rect();
        collider->x = 0;
        collider->y = 0;
        collider->w = 0;
        collider->h = 0;
    }

    Collider(const std::string& tag, int x, int y, int size) : tag(tag)
    {
        collider->x = x;
        collider->y = y;
        collider->w = size;
        collider->h = size;
    }

    ~Collider()
    {
        SDL_DestroyTexture(tex);
        delete transf;
    }

    void Init() override
    {
        if (!entity->HasComponent<Transform>())
            entity->AddComponent<Transform>();

        transf = &entity->GetComponent<Transform>();

        tex = TextureManager::Load("../assets/temp_tile.PNG");

        src = new SDL_Rect();
        src->x = 0;
        src->y = 0;
        src->w = 32;
        src->h = 32;

        dst = new SDL_Rect();
        dst->x = collider->x;
        dst->y = collider->y;
        dst->w = collider->w;
        dst->h = collider->h;
    }

    void Update() override
    {
        if (tag != "terrain")
        {
            collider->x = static_cast<int>(transf->pos.x);
            collider->y = static_cast<int>(transf->pos.y);
            collider->w = transf->width * transf->scale;
            collider->h = transf->height * transf->scale;
        }

        dst->x = collider->x - Game::camera->x;
        dst->y = collider->y - Game::camera->y;
    }

    void Draw() override
    {
        TextureManager::Draw(tex, src, dst, SDL_FLIP_NONE);
    }
};
} // namespace GAlpha