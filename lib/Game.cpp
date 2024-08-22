#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "TileMap.h"

#include "ECS.h"
#include "Component.h"

using namespace GAlpha;

GameObject* player;
GameObject* enemy;

TileMap* map;

SDL_Renderer* Game::renderer = nullptr;

Manager* manager;
auto& new_player(manager->AddEntity());

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

	player = new GameObject("../assets/player_temp.png", 0, 0);
	enemy = new GameObject("../assets/enemy_temp.png", 200, 200);

	map = new TileMap();
	if(!map)
	{
		printf("Map was not loaded!\n");
		return;
	}

	new_player.AddComponent<Position>();

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
	player->Update();
	enemy->Update();
	manager->Update();

	auto pos = new_player.GetComponent<Position>();
	printf("%d %d\n", pos.X(), pos.Y());
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	player->Render();
	enemy->Render();

	map->DrawMap();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}