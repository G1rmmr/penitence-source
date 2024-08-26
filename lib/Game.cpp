#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"

#include "Components.h"

using namespace GAlpha;

TileMap* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player = manager.AddEntity();

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

	map = new TileMap();
	if(!map)
	{
		printf("Map was not loaded!\n");
		return;
	}

	player.AddComponent<Transform>();
	player.AddComponent<Sprite>("../assets/player_temp/png");

	is_running = true;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;

	default: break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	player.GetComponent<Transform>().pos.Add(
		Vector2D(5.0f, 0.0f));

	if(player.GetComponent<Transform>().pos.x > 100)
		player.GetComponent<Sprite>().SetTexture(
			".../assets/player_temp.png");
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();

	manager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}