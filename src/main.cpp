// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#include <core/Game.hpp>

int main()
{
    G2D::Game game;
    game.Init();

    while(game.IsRunning())
        game.Run();
        
    game.Shutdown();
    return 0;
}