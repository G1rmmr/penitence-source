#include <SDL2/SDL.h>

#include <cstdio>

const char* WINDOW_TITLE = "A window";

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const SDL_Color GREEN{0, 255, 0, 255};
const SDL_Color PURPLE{255, 0, 255, 255};

void PrintError()
{
    fprintf(stderr, "SDL Initialization FAIL : %s\n", SDL_GetError());
}

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    auto init = SDL_CreateWindowAndRenderer(
        WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        &window, &renderer);

    if(init < 0)
    {
        PrintError();
        return 1;
    }
    SDL_SetWindowTitle(window, WINDOW_TITLE);

    SDL_Event event;
    bool is_running = true;

    int last_tick = SDL_GetTicks();
    int curr_tick = last_tick;

    int color = 0;

    while(is_running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
        }

        curr_tick = SDL_GetTicks();
        if(curr_tick - last_tick > 100)
        {
            ++color;
            color %= 2;
            last_tick = curr_tick;
        }

        if(!color)
            SDL_SetRenderDrawColor(renderer,
                GREEN.r, GREEN.g, GREEN.b, GREEN.a);
        else
            SDL_SetRenderDrawColor(renderer,
                PURPLE.r, PURPLE.g, PURPLE.b, PURPLE.a);

        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}