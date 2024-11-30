// Created on Wed Oct 30 2024
// © 2024 BLACKHAND Studio. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cassert>

#include "systems/Movement.hpp"
#include "components/Components.hpp"

using namespace MIR;

void Movement::Update(ECSManager& manager, const float dt)
{
    std::vector<Entity::ID> entities = manager.Query<Position, Velocity, PlayerState, Sprite>();

    for(const auto& id : entities)
    {
        Position* pos = manager.GetComponent<Position>(id);
        Velocity* vel = manager.GetComponent<Velocity>(id);
        PlayerState* state = manager.GetComponent<PlayerState>(id);
        Sprite* spr = manager.GetComponent<Sprite>(id);

        switch(state->now_state)
        {
        case PlayerState::Idle:
            vel->x = 0.f;
            vel->y = 0.f;
            break;
        
        case PlayerState::MovingLeft:
            vel->x = -200.f;
            spr->sprite.setScale(-0.5f, 0.5f);
            break;

        case PlayerState::MovingRight:
            vel->x = 200.f;
            spr->sprite.setScale(0.5f, 0.5f);
            break;

        case PlayerState::Jumping:
            break;

        default: break;
        }

        pos->x += vel->x * dt;
        pos->y += vel->y * dt;
    }
}