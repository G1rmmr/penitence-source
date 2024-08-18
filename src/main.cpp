#include "../SDL2/include/SDL.h"

#include "Game.h"
#include "TextureManager.h"

#include <cstdio>

using namespace GAlpha;

// Screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Set FPS
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char* argv[])
{
    Uint32 frame_start = 0;
    int frame_time = 0;

    Game* game = new Game();
    game->Init("ThePenitence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while(game->IsRunning())
    {
        frame_start = SDL_GetTicks();
        
        game->HandleEvents();
        game->Update();
        game->Render();

        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
    }
    game->Clean();
    return 0;
}
