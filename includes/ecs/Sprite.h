#pragma once

#include <unordered_map>

#include <SDL.h>

#include "Animation.h"
#include "Components.h"

#include "../AssetManager.h"
#include "../TextureManager.h"

namespace GAlpha
{
class Sprite : public Component
{
  public:
    std::unordered_map<const char *, Animation *> anims;
    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;
    int anim_index = 0;

    Sprite() = default;

    Sprite(const std::string &id)
    {
        SetTexture(id);
    }

    Sprite(const std::string &id, bool is_anim)
    {
        this->is_anim = is_anim;

        Animation *idle = new Animation(0, 3, 100);
        anims.emplace("IDLE", idle);

        Animation *move = new Animation(1, 6, 100);
        anims.emplace("MOVE", move);

        Animation *jump = new Animation(2, 6, 100);
        anims.emplace("JUMP", jump);

        Play("IDLE");
        SetTexture(id);
    }

    ~Sprite()
    {
        SDL_DestroyTexture(tex);
        delete transf;
    }

    void Init() override
    {
        transf = &entity->GetComponent<Transform>();

        src = SDL_Rect(0, 0, transf->width, transf->height);
        dst = SDL_Rect();
    }

    void Update() override
    {
        if (is_anim)
            src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        src.y = anim_index * transf->height;

        dst.x = static_cast<int>(transf->pos.x) - Game::camera.x;
        dst.y = static_cast<int>(transf->pos.y) - Game::camera.y;
        dst.w = transf->width * transf->scale;
        dst.h = transf->height * transf->scale;
    }

    void Draw() override
    {
        TextureManager::Draw(tex, src, dst, sprite_flip);
    }

    inline void SetTexture(const std::string &id)
    {
        tex = Game::assets.GetTexture(id);
    }

    void Play(const char *anim_name)
    {
        auto anim = anims[anim_name];

        frames = anim->frames;
        anim_index = anim->index;
        speed = anim->speed;
    }

  private:
    SDL_Texture *tex;
    SDL_Rect src;
    SDL_Rect dst;

    Transform *transf;

    int frames = 0;
    int speed = 100;

    bool is_anim = false;
};
} // namespace GAlpha