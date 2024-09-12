#include "Components.h"

namespace GAlpha
{
class Animation
{
public:
    int index;
    int frames;
    int speed;

    Animation()
    {
    }

    Animation(int index, int frames, int speed)
    : index(index), frames(frames), speed(speed)
    {
    }
};
} // namespace GAlpha