// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

#include <cstdio>
#include <string>

#include "Core.hpp"

namespace G2D
{
    class Game
    {
    public:
        inline static const uint16_t WINDOW_WIDTH = 800;
        inline static const uint16_t WINDOW_HEIGHT = 600;
        inline static const std::string WINDOW_TITLE = "The Penitence";

        inline static const uint8_t PROTAGONIST_WIDTH = 128;
        inline static const uint8_t PROTAGONIST_HEIGHT = 128;

        enum class ProtState : uint8_t
        {
            Idle,
            Move,
            Jump,
            Fall
        };

        Game() = default;

        void Init();
        void HandleEvent();
        void Update();
        void Run();
        void Render();
        void Shutdown();

        inline bool IsRunning() const
        {
            return window.isOpen();
        }

    private:
        sf::RenderWindow window;
        sf::Event event;
        
        World world;

        Entity protagonist;
        ProtState now_state = ProtState::Idle;
    };
}