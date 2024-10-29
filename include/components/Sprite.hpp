// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <string>
#include <cstdio>

#include "Component.hpp"

namespace G2D
{
    struct Sprite final : public Component
    {
        sf::Texture texture;
        sf::Sprite sprite;
    };
}