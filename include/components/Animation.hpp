// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <vector>

#include "Component.hpp"

namespace G2D
{
    struct Animation final : public Component
    {
        std::vector<sf::IntRect> frames;

        float delay;
        float elapsed;

        uint8_t num_frame;
        uint8_t curr;
        uint8_t type;
    };
}