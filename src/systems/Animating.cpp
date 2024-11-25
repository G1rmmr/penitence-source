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

void Animating::Update(ECSManager& manager, const float dt)
{
    auto entities = manager.Query<Animation, Sprite>();

    for(const auto id : entities)
    {
        Animation* anim = manager.GetComponent<Animation>(id);
        Sprite* spr = manager.GetComponent<Sprite>(id);

        if(!anim->is_playing || anim->frames.empty())
             continue;

        anim->elapsed += dt;

        if(anim->elapsed >= anim->delay)
        {
            anim->elapsed = 0.f;
            anim->curr_frame++;
            
            if(anim->curr_frame >= anim->frames.size())
            {
                if(anim->is_looping)
                    anim->curr_frame = 0;
                else
                {
                    anim->curr_frame--;
                    anim->is_playing = false;
                }
            }
            spr->sprite.setTextureRect(anim->frames[anim->curr_frame]);
        }
    }
}