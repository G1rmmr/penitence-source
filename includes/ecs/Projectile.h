#pragma once

#include "ECS.h"
#include "Components.h"

#include "../Vector2D.h"

namespace GAlpha
{
    class Projectile : public Component
    {
    public:
        Projectile(int range, int speed, Vector2D vel)
        : range(range), speed(speed), vel(vel)
        {

        }

        ~Projectile();

        void Init() override
        {
            transf = &entity->GetComponent<Transform>();
            transf->vel = vel;
        }

        void Update() override
        {
            distance += speed;

            if(distance > range) entity->Destroy();

            if(transf->pos.x < Game::camera->x)
                entity->Destroy();

            if(transf->pos.x > Game::camera->x + Game::camera->w )
                entity->Destroy();

            if(transf->pos.y < Game::camera->y)
                entity->Destroy();

            if(transf->pos.y > Game::camera->y + Game::camera->h)
                entity->Destroy();
        }


    private:
        Transform* transf;

        Vector2D vel;

        int range = 0;
        int speed = 0;
        int distance = 0;
    };
}