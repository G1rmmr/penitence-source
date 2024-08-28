#include "Game.h"

#include "ecs/Components.h"
#include "TextureManager.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace GAlpha;

Map* map;
Manager* manager;

std::vector<Collider*> Game::colliders;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager->AddEntity());
auto& wall(manager->AddEntity());

enum GroupLabels : std::size_t
{
	GROUP_MAP,
	GROUP_PLAYERS,
	GROUP_ENEMIES,
	GROUP_COLLIDERS
};

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

	map = new Map();
	if(!map)
	{
		printf("Map was not loaded!\n");
		return;
	}

	player.AddComponent<Transform>(2);
	player.AddComponent<Sprite>("../assets/player_temp.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<Collider>("player");
	player.AddGroup(GROUP_PLAYERS);

	wall.AddComponent<Transform>(300.0f, 300.0f, 20.0f, 300.0f, 1.0f);
	wall.AddComponent<Sprite>("../assets/enemy_temp.png");
	wall.AddComponent<Collider>("wall");
	wall.AddGroup(GROUP_MAP);

	is_running = true;
}

void Game::HandleEvents()
{
	SDL_PollEvent(&Game::event);

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
	manager->Refresh();
	manager->Update();

	for(auto collid : colliders)
		Collision::BothAABBCollide(player.GetComponent<Collider>(), *collid);
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->Draw();

	manager->Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}

void Game::AddTile(int src_x, int src_y, int x, int y)
{
	auto& tile(manager->AddEntity());
	tile.AddComponent<Tile>(x, y, 150, 150, id);
	tile.AddGroup(GROUP_MAP);
}