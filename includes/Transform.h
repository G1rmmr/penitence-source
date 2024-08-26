#pragma once

#include "Components.h"
#include "Vector2D.h"

namespace GAlpha
{
    class Transform : public Component
    {
    public:
        Vector2D pos;
        Vector2D vel;

        const float speed = 3.0f;

        Transform() : pos(0.0f, 0.0f)
        {

        }
        
        Transform(float x, float y) : pos(x, y) 
        {

        }

        void SetPos(float x, float y)
        {
            pos.x = x;
            pos.y = y;
        }
        
        void Init() override
        {
            vel = Vector2D(0.0f, 0.0f);
            pos = Vector2D(0.0f, 0.0f);
        }

        void Update() override
        {
            pos.x += vel.x * speed;
            pos.y += vel.y * speed;
        }
    };
}