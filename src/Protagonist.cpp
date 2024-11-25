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
    id = manager.CreateEntity();

    if(USING_SAVE_FILE)
        storage.Load(manager);
    else
        manager.AddComponent<Position>(id, INIT_WIDTH, INIT_HEIGHT);

    manager.AddComponent<Velocity>(id);

    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if(texture->loadFromFile(IMG_PATH))
    {
        Position* pos = manager.GetComponent<Position>(id);

        auto spr = std::make_shared<Sprite>(texture);
        spr->sprite.setPosition(pos->x, pos->y);
        spr->sprite.setScale(0.5f, 0.5f);
        spr->sprite.setTextureRect(sf::IntRect{
            0, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});

        manager.AddComponent<Sprite>(id, texture, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT);

        std::vector<sf::IntRect> frames;
        float delay = 1.f / 6.f;
        std::uint8_t num_frame = 4;
        manager.AddComponent<Animation>(id, frames, delay, 0.f, num_frame, 0);
    }
    else
        fprintf(stderr, "TEXTURE NOT FOUND!\n");

    manager.AddComponent<PlayerState>(id);
}