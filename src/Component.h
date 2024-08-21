#pragma once

#include "ECS.h"

namespace GAlpha
{
    class Position : public Component
    {
    public:
        int X() const {return x;}
        int Y() const {return y;}

        void SetPos(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        
        void Init() override
        {
            this->x = 0;
            this->y = 0;
        }

        void Update() override
        {
            x++;
            y++;
        }

    private:
        int x = 0;
        int y = 0;
    };
}