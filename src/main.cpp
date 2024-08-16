#include "../SDL2/include/SDL.h"

#include "Entity.h"
#include "MovementComponents.h"
#include "MovementSystem.h"

#include <cstdio>

using namespace GAlpha;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int FPS = 60;
const float DELTA_TIME = 0.016f;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
	{
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());

        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
	{
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set player
    Entity player(1);

    const int player_vel = 20;
    const int player_width = 200;
    const int player_height = 300;

    Position p_pos;
    p_pos.x = 200.0f;
    p_pos.y = 150.0f;
    
    Velocity p_vel;
    p_vel.dx = 0.0f;
    p_vel.dy = 0.0f;

    player.AddComponent(std::make_shared<Position>(p_pos));
    player.AddComponent(std::make_shared<Velocity>(p_vel));

    MovementSystem* movement;

    // Set Game State
    bool is_running = true;
    SDL_Event* event = new SDL_Event();

    while (is_running)
	{
        while (SDL_PollEvent(event))
		{
            if(event->type == SDL_QUIT)is_running = false;

            if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            {
                auto vel = player.GetComponent<Velocity>();

                switch (event->key.keysym.sym)
                {
                case SDLK_w:
                    vel->dy = (event->type == SDL_KEYDOWN) ? -player_vel : 0;
                    break;
                
                case SDLK_a:
                    vel->dx = (event->type == SDL_KEYDOWN) ? -player_vel : 0;
                    break;

                case SDLK_s:
                    vel->dy = (event->type == SDL_KEYDOWN) ? player_vel : 0;
                    break;

                case SDLK_d:
                    vel->dx = (event->type == SDL_KEYDOWN) ? player_vel : 0;
                    break;

                default:
                    break;
                }
            }
        }

        movement->Update(player, DELTA_TIME);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        auto pos = player.GetComponent<Position>();

        SDL_Rect* fill_rect = new SDL_Rect();
        fill_rect->x = static_cast<int>(pos->x);
        fill_rect->y = static_cast<int>(pos->y);
        fill_rect->w = player_width;
        fill_rect->h = player_height;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, fill_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
