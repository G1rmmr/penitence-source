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

#include <SFML/Graphics.hpp>
#include "systems/Rendering.hpp"
#include "components/Components.hpp"

using namespace MIR;
using namespace ECS;

void Rendering::Update(Manager& manager, const float dt)
{
    std::vector<Entity::ID> entities = manager.Query<Position, Sprite>();

    for(auto& id : entities)
    {
        Sprite* spr = manager.GetComponent<Sprite>(id);
        Position* pos = manager.GetComponent<Position>(id);
        spr->sprite.setPosition({pos->x, pos->y});
    }
}

void Rendering::Render(Manager& manager, sf::RenderWindow& window)
{
    std::vector<Entity::ID> entities = manager.Query<Sprite>();

    for(const auto& id : entities)
    {
        Sprite* spr = manager.GetComponent<Sprite>(id);
        
        if(spr && spr->texture && spr->texture->getSize().x > 0 && spr->texture->getSize().y > 0)
            window.draw(spr->sprite);
    }
}
