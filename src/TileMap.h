#pragma once

#include "Game.h"

namespace GAlpha
{
	class TileMap
	{
	public:
		TileMap();
		~TileMap();

		void LoadMap(int lv[20][25]);
		void DrawMap();

	private:
		SDL_Rect* src;
		SDL_Rect* dest;

		SDL_Texture* elem1;
		SDL_Texture* elem2;

		int map[20][25];
	};
}