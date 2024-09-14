#include "Components.h"

namespace GAlpha
{
	class Animation : public Component
	{
	public:
		int index = 0;
		int frames = 0;
		int speed = 0;

		Animation() = default;

		Animation(int index, int frames, int speed)
			: index(index), frames(frames), speed(speed)
		{
		}
	};
} // namespace GAlpha