#include "Game.h"
#include "TextureManager.h"

using namespace GAlpha;

SDL_Texture* player_tex;
SDL_Rect* player_rect, dest_rect;

int count = 0;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char *title, int x, int y, int w, int h, bool is_full)
{
	int full_screen_flag = is_full ? SDL_WINDOW_FULLSCREEN : 0;

	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("System was not initialized!\n");
		return;
	}


	window = SDL_CreateWindow(title, x, y, w, h, full_screen_flag);
	if(!window)
	{
		printf("Window was not created!\n");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
	{
		printf("Renderer was not created!\n");
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	player_tex = TextureManager::LoadTexture(
		"../assets/player_temp", renderer);
		
	if(!player_tex) return;

	is_running = true;
}

void Game::HandleEvents()
{
	SDL_Event* event = new SDL_Event();
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
	dest_rect.h = 32;
	dest_rect.w = 32;
	dest_rect.x = ++count;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, player_tex, nullptr, &dest_rect);

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}