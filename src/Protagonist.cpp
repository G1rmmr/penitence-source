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

#include "Protagonist.hpp"

using namespace MIR;

void Protagonist::Init(ECSManager& manager, Storage& storage)
{
    // ID set
    id = manager.CreateEntity();

    // Position set
    if(USING_SAVE_FILE)
        storage.Load(manager);
    else
        manager.AddComponent<Position>(id, INIT_WIDTH, INIT_HEIGHT);

    // Velocity set
    manager.AddComponent<Velocity>(id);

    // Sprite set
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if(texture->loadFromFile(IMG_PATH))
    {
        manager.AddComponent<Sprite>(id, texture, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT);
        Sprite* spr = manager.GetComponent<Sprite>(id);
        spr->sprite.setScale(0.5f, 0.5f);
        spr->sprite.setTextureRect({0, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});
    }
    else
        fprintf(stderr, "TEXTURE NOT FOUND!\n");

    // State set
    manager.AddComponent<PlayerState>(id);

    // Animation set
    manager.AddComponent<Animation>(id);
    
    Animation* anim = manager.GetComponent<Animation>(id);

    for(std::size_t i = 0; i < 4; ++i)
        anim->frames.emplace_back(sf::IntRect{
            static_cast<int>(i * PROTAGONIST_WIDTH), 0,
            static_cast<int>(PROTAGONIST_WIDTH),
            static_cast<int>(PROTAGONIST_HEIGHT)});
}