#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cstdio>
#include <vector>

class Collider;
namespace GAlpha
{
	class Game
	{
	public:
		Game();
		~Game();

		void Init(const char* title, int x, int y, int w, int h, bool is_full);
		void HandleEvents();

		void Update();
		void Render();
		void Clean();

		bool IsRunning() const {return Game::is_running;}

		static std::vector<Collider*> colliders;
		static SDL_Renderer* renderer;
		static SDL_Event event;

		static SDL_Rect* camera;
		static bool is_running;

		static void AddTile(int src_x, int src_y, int x, int y);

		// Screen size

		static int SCREEN_WIDTH;
		static int SCREEN_HEIGHT;

		// Set FPS
		static int FPS;
		static int FRAME_DELAY;

	private:
		SDL_Window* window;
	};
}