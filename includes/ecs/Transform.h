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

    bool is_blocked = false;

    Transform() : pos(0.0f, 0.0f)
    {
    }

    Transform(float x, float y) : pos(x, y)
    {
    }

    Transform(float scale)
    : pos(), width(0.0f), height(0.0f), scale(scale)
    {
        pos.Zero();
    }

    Transform(float x, float y, float w, float h, float scale)
    : pos(), width(w), height(h), scale(scale)
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