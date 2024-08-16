#pragma once

#include "../SDL2/include/SDL.h"
#include "Entity.h"
#include "MovementComponents.h"

#include <iostream>

namespace GAlpha
{
    class MovementSystem
    {
    public:
        void Update(Entity& entity, float delta_time)
        {
            auto pos = entity.GetComponent<Position>();
            auto vel = entity.GetComponent<Velocity>();

            if(pos && vel)
            {
                pos->x += vel->dx * delta_time;
                pos->y += vel->dy * delta_time;
            }
        }
    };
}