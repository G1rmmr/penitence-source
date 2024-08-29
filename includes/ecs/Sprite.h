#pragma once

#include <SDL.h>

#include "Components.h"
#include "Animation.h"

#include "../TextureManager.h"
#include "../Map.h"

namespace GAlpha
{
    class Sprite : public Component
    {
    public:
        std::unordered_map<const char*, Animation> anims;
        SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;
        int anim_index = 0;

        Sprite() = default;

        Sprite(const char* path, bool is_anim)
        {
            this->is_anim = is_anim;

            Animation idle = Animation(0, 3, 100);
            anims["IDLE"] = idle;

            Animation walk = Animation(1, 3, 100);
            anims["WALK"] = walk;

            Play("IDLE");
            SetTexture(path);
        }

        ~Sprite()
        {
            SDL_DestroyTexture(tex);
        }

        void SetTexture(const char* path)
        {
            tex = TextureManager::Load(path);
        }

        void Init() override
        {
            transf = &entity->GetComponent<Transform>();

            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = transf->width;
            src->h = transf->height;

            dst = new SDL_Rect();
            dst->x = 0;
            dst->y = 0;
            dst->w = 0;
            dst->h = 0;
        }

        void Update() override
        {
            if(is_anim)
                src->x = src->w * static_cast<int>(
                    (SDL_GetTicks() / speed) % frames);

            src->y = anim_index * transf->height;

            dst->x = static_cast<int>(transf->pos.x) - Game::camera->x;
            dst->y = static_cast<int>(transf->pos.y) - Game::camera->y;
            dst->w = transf->width * transf->scale;
            dst->h = transf->height * transf->scale;
        }

        void Draw() override
        {
            TextureManager::Draw(tex, src, dst, sprite_flip);
        }

        void Play(const char* anim_name)
        {
            auto anim = anims[anim_name];

            frames = anim.frames;
            anim_index = anim.index;
            speed = anim.speed;
        }

    private:
        SDL_Texture* tex;
        SDL_Rect* src;
        SDL_Rect* dst;

        Transform* transf;

        int frames = 0;
        int speed = 100;

        bool is_anim = false;

    };
}