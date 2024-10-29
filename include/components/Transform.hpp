// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace G2D
{
    struct Transform final : public Component
    {
        sf::Vector2f pos;
        sf::Vector2f vel;
    };
    
}