#include "Game.h"

#include "ecs/Components.h"

#include "AssetManager.h"
#include "Collision.h"
#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"

using namespace GAlpha;

// Screen size
int Game::SCREEN_WIDTH = 1280;
int Game::SCREEN_HEIGHT = 960;

// Set FPS
int Game::FPS = 24;
int Game::FRAME_DELAY = 1000 / FPS;

Map* map;
Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect* Game::camera = new SDL_Rect{
	0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT};

bool Game::is_running = false;

auto& player(manager.AddEntity());

Game::Game()
{
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
}

void Game::Init(const char* title, int x, int y, int w, int h, bool is_full)
{
	int full_screen_flag = is_full ? SDL_WINDOW_FULLSCREEN : 0;

	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("System was not initialized!\n");
		return;
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("Image loader not initialized with PNG format!\n");
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

	SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0xF0, 0xF0);

	assets->AddTexture("Player", "C:/Blackhand Studio/penitence-source/assets/player_anim.PNG");
	assets->AddTexture("terrain", "C:/Blackhand Studio/penitence-source/assets/temp_tile.PNG");

	map = new Map("terrain", 0, 0);

	player.AddComponent<Transform>(200, 300, 128, 128, 3);
	player.AddComponent<Sprite>("Player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<Collider>("Player");
	player.AddGroup(GROUP_PLAYERS);

	is_running = true;
	printf("GAME IS READY\n");
}

auto& tiles(manager.GetGroup(Game::GROUP_MAP));
auto& players(manager.GetGroup(Game::GROUP_PLAYERS));
auto& colliders(manager.GetGroup(Game::GROUP_COLLIDERS));
auto& projs(manager.GetGroup(Game::GROUP_PROJECTILES));

void Game::HandleEvents()
{
	SDL_PollEvent(&Game::event);

	switch(Game::event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;

	default:
		break;
	}
}

void Game::Update()
{
	SDL_Rect* player_coll = player.GetComponent<Collider>().collider;
	Vector2D player_pos = player.GetComponent<Transform>().pos;

	manager.Refresh();
	manager.Update();

	for(auto& elem : colliders)
	{
		SDL_Rect* elem_coll = elem->GetComponent<Collider>().collider;

		if(Collision::BothAABBCollide(elem_coll, player_coll))
		{
			player.GetComponent<Transform>().pos = player_pos;
		}
	}

	for(auto& proj : projs)
	{
		if(Collision::BothAABBCollide(
			player.GetComponent<Collider>().collider,
			proj->GetComponent<Collider>().collider))
			proj->Destroy();
	}

	camera->x = static_cast<int>(
		player.GetComponent<Transform>().pos.x
		- Game::SCREEN_WIDTH * 0.5f);

	camera->y = static_cast<int>(
		player.GetComponent<Transform>().pos.y
		- Game::SCREEN_HEIGHT * 0.5f);

	camera->x = camera->x < 0 ? 0 : camera->x;
	camera->x = camera->x > camera->w ? camera->w : camera->x;

	camera->y = camera->y < 0 ? 0 : camera->y;
	camera->y = camera->y > camera->h ? camera->h : camera->y;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	// for (auto &tile : tiles) tile->Draw();
	// for (auto &coll : colliders) coll->Draw();
	for(auto& p : players) p->Draw();
	// for (auto &proj : projs) proj->Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Game Cleaned!\n");
}