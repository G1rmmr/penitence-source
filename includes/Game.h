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

		bool IsRunning() const {return is_running;}

		static std::vector<Collider*> colliders;
		static SDL_Renderer* renderer;
		static SDL_Event event;

		static void AddTile(int id, int x, int y);

	private:
		SDL_Window* window;
		
		bool is_running;
	};
}