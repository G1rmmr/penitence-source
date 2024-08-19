#pragma once

#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_image.h"

#include <cstdio>

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

		static SDL_Renderer* renderer;

	private:
		SDL_Window* window;
		
		bool is_running;
	};
}