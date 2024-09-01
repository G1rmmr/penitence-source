#include "Game.h"

#include "ecs/Components.h"
#include "TextureManager.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace GAlpha;

// Screen size

int Game::SCREEN_WIDTH = 1920;
int Game::SCREEN_HEIGHT = 1080;

// Set FPS
int Game::FPS = 24;
int Game::FRAME_DELAY = 1000 / FPS;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<Collider*> Game::colliders;

SDL_Rect* Game::camera = new SDL_Rect{
	0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT};

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

const char* map_path = "";

bool Game::is_running = false;

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
	player.AddComponent<Sprite>("../assets/player_anim.PNG", true);
	player.AddComponent<KeyboardController>();

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
	manager.Refresh();
	manager.Update();

	camera->x = player.GetComponent<Transform>().pos.x
		- Game::SCREEN_WIDTH * 0.5f;

	camera->y = player.GetComponent<Transform>().pos.y
		- Game::SCREEN_HEIGHT * 0.5f;

	camera->x = camera->x < 0 ? 0 : camera->x;
	camera->x = camera->x > camera->w ? camera->w : camera->x;

	camera->y = camera->y < 0 ? 0 : camera->y;
	camera->y = camera->y > camera->h ? camera->h : camera->y;
}



void Game::Render()
{
	SDL_RenderClear(renderer);

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

void Game::AddTile(int src_x, int src_y, int x, int y)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<Tile>(src_x, src_y, x, y, map_path);
	tile.AddGroup(GROUP_MAP);
}