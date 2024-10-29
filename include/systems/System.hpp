// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <vector>
#include <memory>

#include "core/Entity.hpp"
#include "core/World.hpp"

namespace G2D
{
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;
        
        virtual void Update(Entity& entity, const float dt) = 0;
        virtual void Render(Entity& entity) = 0;
    };
}
