// Created on Sun Nov 24 2024
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

#include "systems/Animating.hpp"
#include "components/Components.hpp"

using namespace MIR;
using namespace ECS;

void Animating::Update(Manager& manager, const float dt)
{
    auto entities = manager.Query<Animation, Sprite>();

    for(const auto id : entities)
    {
        Animation* anim = manager.GetComponent<Animation>(id);
        Sprite* spr = manager.GetComponent<Sprite>(id);

        // 플레이어 상태에 따라 애니메이션 프레임 세트 변경
        if(manager.HasComponent<PlayerState>(id))
        {
            PlayerState* state = manager.GetComponent<PlayerState>(id);
            anim->frames.clear();

            std::uint8_t index = -1;
            std::size_t frame_size = -1;

            switch(state->now_state)
            {
            case PlayerState::Idle:
                index = 0;
                frame_size = 4;
                break;

            case PlayerState::Jumping:
                index = 2;
                frame_size = 6;
                break;
                
            default:
                index = 1;
                frame_size = 6;
                break;
            }

            // 상태에 따라 지정된 frame_size 만큼 프레임을 생성
            for(std::size_t i = 0; i < frame_size; ++i)
                anim->frames.emplace_back(sf::IntRect{
                    static_cast<int>(i * spr->width),
                    static_cast<int>(index * spr->height),
                    static_cast<int>(spr->width),
                    static_cast<int>(spr->height)});
        }

        // 애니메이션 재생 중이 아니거나 프레임이 없는 경우 처리 안 함
        if(!anim->is_playing || anim->frames.empty())
             continue;

        anim->elapsed += dt;

        // delay 시간 경과 시 다음 프레임으로 전환
        if(anim->elapsed >= anim->delay)
        {
            anim->elapsed = 0.f;
            anim->curr_frame++;
            
            if(anim->curr_frame >= anim->frames.size())
            {
                // 루프 가능한 애니메이션이면 0 프레임으로 돌아감
                if(anim->is_looping)
                    anim->curr_frame = 0;
                else
                {
                    // 루프 불가 시 마지막 프레임에서 정지
                    anim->curr_frame--;
                    anim->is_playing = false;
                }
            }

            // 스프라이트에 새로운 프레임 텍스처 영역 적용
            spr->sprite.setTextureRect(anim->frames[anim->curr_frame]);
        }
    }
}
