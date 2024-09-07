#include <cstdio>

#include <SDL.h>

#include "Game.h"
#include "TextureManager.h"

using namespace GAlpha;

int main(int argc, char *argv[])
{
    Uint32 frame_start = 0;
    int frame_time = 0;

    Game *game = new Game();
    game->Init("ThePenitence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT,
               false);

    while (game->IsRunning())
    {
        frame_start = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frame_time = SDL_GetTicks() - frame_start;

        if (Game::FRAME_DELAY > frame_time)
            SDL_Delay(Game::FRAME_DELAY - frame_time);
    }
    game->Clean();

    return 0;
}