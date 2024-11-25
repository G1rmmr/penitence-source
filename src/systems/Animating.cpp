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
    std::vector<Entity::ID> entities = manager.Query<Sprite, PlayerState, Animation>();

    for(auto& id : entities)
    {
        Animation* anim = manager.GetComponent<Animation>(id);
        Sprite* spr = manager.GetComponent<Sprite>(id);
        PlayerState* state = manager.GetComponent<PlayerState>(id);

        if(anim->frames.empty())
            continue;

        anim->frames.clear();

        for(std::uint8_t i = 0; i < anim->num_frame; ++i)
            anim->frames.emplace_back(sf::IntRect{
                i * spr->width, state->now_state * spr->height,
                    spr->width, spr->height});

        anim->elapsed += dt;

        if(anim->elapsed >= anim->delay)
        {
            anim->elapsed = 0.f;
            anim->curr = (anim->curr + 1) % anim->frames.size();
            spr->sprite.setTextureRect(anim->frames[anim->curr]);
        }
    }
}