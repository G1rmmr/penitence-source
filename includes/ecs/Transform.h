#pragma once

#include "Components.h"

#include "../Vector2D.h"

namespace GAlpha
{
class Transform : public Component
{
public:
    Vector2D pos;
    Vector2D vel;

    const float SPEED = 3.0f;

    float width = 128.0f;
    float height = 128.0f;
    float scale = 1.0f;

    Transform() : pos(0.0f, 0.0f)
    {
    }

    Transform(float x, float y) : pos(x, y)
    {
    }

    Transform(int scale)
    : pos(0.0f, 0.0f), width(0.0f), height(0.0f), scale(scale)
    {
    }

    Transform(float x, float y, float w, float h, float scale)
    : pos(x, y), width(w), height(h), scale(scale)
    {
        pos.x = x;
        pos.y = y;
    }

    void SetPos(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }

    void Init() override
    {
        vel.Zero();
        pos.Zero();
    }

    void Update() override
    {
        pos.x += vel.x * SPEED;
        pos.y += vel.y * SPEED;
    }
};
} // namespace GAlpha