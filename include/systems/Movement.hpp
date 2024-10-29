// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include "System.hpp"

namespace G2D
{
    class Movement final : public System
    {
    public:
        void Update(Entity& entity, const float dt) override final;
        void Render(Entity& entity) override final
        {
            return;
        }
    };
}