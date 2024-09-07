#pragma once

#include <unordered_map>

#include <SDL.h>

#include "Components.h"
#include "Animation.h"

#include "../TextureManager.h"
#include "../AssetManager.h"

namespace GAlpha
{
    class Sprite : public Component
    {
    public:
        std::unordered_map<const char*, Animation*> anims;
        SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;
        int anim_index = 0;

        Sprite() = default;

        Sprite(const std::string& id)
        {
            SetTexture(id);
        }

        Sprite(const std::string& id, bool is_anim)
        {
            this->is_anim = is_anim;

            Animation* idle = new Animation(0, 3, 100);
            anims.emplace("IDLE", idle);

            Animation* move = new Animation(1, 6, 100);
            anims.emplace("MOVE", move);

            Animation* jump = new Animation(2, 6, 100);
            anims.emplace("JUMP", jump);

            Play("IDLE");
            SetTexture(id);
        }

        ~Sprite()
        {
            SDL_DestroyTexture(tex);

            delete transf;
            delete src;
            delete dst;
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

        inline void SetTexture(const std::string& id)
        {
            tex = Game::assets->GetTexture(id);
        }

        void Play(const char* anim_name)
        {
            auto anim = anims[anim_name];

            frames = anim->frames;
            anim_index = anim->index;
            speed = anim->speed;
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