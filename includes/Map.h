#pragma once

#include "Game.h"

namespace GAlpha
{
	class Map
	{
	public:
		Map();
		~Map();

		static void Load(const char* path, int size_x, int size_y);
	};
}