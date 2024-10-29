// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include "Component.hpp"

namespace G2D
{
    struct InputBehavior final : public Component
    {
        bool up = false;
        bool left = false;
        bool down = false;
        bool right = false;
    };
}