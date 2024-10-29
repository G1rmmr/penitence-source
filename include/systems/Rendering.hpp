// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include "System.hpp"

namespace G2D
{
    class Rendering final : public System
    {
    public:
        void Update(Entity& entity, const float dt) override final;
        void Render(Entity& entity) override final;

        void SetWindow(sf::RenderWindow* r_window);

    private:
        sf::RenderWindow* window = nullptr;
    };
}