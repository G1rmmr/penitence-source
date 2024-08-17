#include "Game.h"

using namespace GAlpha;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char *title, int x, int y, int w, int h, bool is_full)
{
	int full_screen_flag = is_full ? SDL_WINDOW_FULLSCREEN : 0;

	if(!SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("System Initialized!\n");

		window = SDL_CreateWindow(title, x, y, w, h, full_screen_flag);
		if(window) printf("Window created!\n");

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			printf("Renderer created!\n");

		}

		is_running = true;
	}
	else is_running = false;
}

void Game::HandleEvents()
{
	SDL_Event* event;
	SDL_PollEvent(event);

	switch(event->type)
	{
	case SDL_QUIT:
		is_running = false;
		break;

	default: break;
	}
}

void Game::Update()
{

}

void Game::Render()
{
	SDL_RenderClear(renderer);

	// Render what you want

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}