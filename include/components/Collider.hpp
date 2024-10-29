// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace G2D
{
    struct Collider final : public Component
    {
        sf::FloatRect box;
    };
}