#pragma once

#include <SFML/Graphics.hpp>

#include <cstdio>
#include <string>

namespace GEngine
{
    class Game
    {
    public:
        inline static const uint16_t WINDOW_WIDTH = 800;
        inline static const uint16_t WINDOW_HEIGHT = 600;
        inline static const std::string WINDOW_TITLE = "The Penitence";

        Game() = default;

        void Init();
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
        sf::CircleShape circle;
    };
}