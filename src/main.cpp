#include "../SDL2/include/SDL.h"

#include "Entity.h"
#include "MovementSystem.h"

#include <cstdio>

using namespace GAlpha;

// Screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Level size
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 1200;

// Set FPS
const int FPS = 60;
const float DELTA_TIME = 0.016f;

// Temporary Func
// TO-DO : It must be designed ECS
bool BothAABBCollide(SDL_Rect* left, SDL_Rect* right)
{
    if (left->x + left->w <= right->x || right->x + right->w <= left->x ||
        left->y + left->h <= right->y || right->y + right->h <= left->y)
        return false;

    return true;
}

// Simple camera system
void UpdateCamera(SDL_Rect& camera, SDL_Rect* player)
{
    camera.x = player->x + (player->w * 0.5f) - (camera.w * 0.5f);
    camera.y = player->y + (player->h * 0.5f) - (camera.h * 0.5f);

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    
    if (camera.x > LEVEL_WIDTH - camera.w)
        camera.x = LEVEL_WIDTH - camera.w;
    
    if (camera.y > LEVEL_HEIGHT - camera.h)
        camera.y = LEVEL_HEIGHT - camera.h;
}

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

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
	{
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set camera
    SDL_Rect* camera = new SDL_Rect();
    camera->x = 0;
    camera->y = 0;
    camera->w = SCREEN_WIDTH;
    camera->h = SCREEN_HEIGHT;

    // Set player
    Entity* player = new Entity(1);

    const int player_vel = 20;

    const float init_player_x = 200.0f;
    const float init_player_y = 150.0f;

    const int player_width = 50;
    const int player_height = 75;

    // Add position component to player
    Position* pos = new Position();
    pos->x = init_player_x;
    pos->y = init_player_y;

    player->AddComponent(std::make_shared<Position>(*pos));

    // Add position component to player
    Velocity* vel = new Velocity();
    vel->dx = 0.0f;
    vel->dy = 0.0f;

    player->AddComponent(std::make_shared<Velocity>(*vel));

    // Add collsion component 
    MovementSystem* movement = new MovementSystem();

    // Set Game State
    bool is_running = true;
    SDL_Event* event = new SDL_Event();

    while (is_running)
	{
        while (SDL_PollEvent(event))
		{
            if(event->type == SDL_QUIT) is_running = false;

            if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            {
                auto vel = player->GetComponent<Velocity>();

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

        auto pos = player->GetComponent<Position>();

        // Render player
        SDL_Rect* player_aabb = new SDL_Rect();
        player_aabb->x = static_cast<int>(pos->x);
        player_aabb->y = static_cast<int>(pos->y);
        player_aabb->w = player_width;
        player_aabb->h = player_height;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, player_aabb);

        // Render AABB box
        const int aabb_x = 400;
        const int aabb_y = 400;

        SDL_Rect* aabb = new SDL_Rect();
        aabb->x = aabb_x;
        aabb->y = aabb_y;
        aabb->w = 30;
        aabb->h = 30;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, aabb);

        // Check Collision
        if(BothAABBCollide(player_aabb, aabb))
        {
            auto pos = player->GetComponent<Position>();
            pos->x = init_player_x;
            pos->y = init_player_y;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
