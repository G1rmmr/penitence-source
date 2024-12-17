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
using namespace ECS;

const float JUMP_SPEED = 500.f;  ///< 점프 시 상승 속도
const float GRAVITY = 980.f;     ///< 중력 가속도 (단위: 픽셀/초² 가정)
const float LEVEL = 500.f;       ///< 지면 레벨(y좌표)

void Movement::Update(Manager& manager, const float dt)
{
    std::vector<Entity::ID> entities = manager.Query<Position, Velocity, PlayerState, Sprite>();

    for(const auto& id : entities)
    {
        Position* pos = manager.GetComponent<Position>(id);
        Velocity* vel = manager.GetComponent<Velocity>(id);
        PlayerState* state = manager.GetComponent<PlayerState>(id);
        Sprite* spr = manager.GetComponent<Sprite>(id);
        
        // 점프 로직: 점프 상태가 아니며 지면에 있을 때 점프 명령 처리
        if(state->now_state == PlayerState::Jumping
            && !state->is_jumping && pos->y >= LEVEL)
        {
            vel->y = -JUMP_SPEED;
            state->is_jumping = true;
        }

        // 상태에 따른 수평 이동 속도 및 스프라이트 스케일 조정
        switch(state->now_state)
        {
        case PlayerState::MovingLeft:
            vel->x = -200.f;
            spr->sprite.setScale(-0.5f, 0.5f);
            break;

        case PlayerState::MovingRight:
            vel->x = 200.f;
            spr->sprite.setScale(0.5f, 0.5f);
            break;

        case PlayerState::Jumping:
            printf("JUMP\n");
            // 점프 중 특별한 수평 변화 없음, vel->x는 유지됨(기본적으로 0)
            break;

        default:
            // Idle 상태 등에서는 수평 속도 0
            vel->x = 0.f;
            break;
        }

        // 중력 적용: 지면 위가 아닐 경우(점프 중) 중력 가속도 적용
        if(pos->y < LEVEL)
            vel->y += GRAVITY * dt;

        // 지면 도달 처리: 지면을 넘어가지 않도록 위치, 상태 보정
        if(pos->y + vel->y * dt >= LEVEL)
        {
            pos->y = LEVEL;
            vel->y = 0.f;
            state->is_jumping = false;

            // 점프 상태에서 지면 도달 시 Idle 상태로 전환
            if(state->now_state == PlayerState::Jumping)
                state->now_state = PlayerState::Idle;
        }

        // 위치 갱신: 속도 * 시간(dt)을 위치에 반영
        pos->x += vel->x * dt;
        pos->y += vel->y * dt;
    }
}
