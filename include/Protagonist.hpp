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

#pragma once

#include "core/Core.hpp"

class Protagonist
{
public:
    Protagonist() = default;

    void Init(MIR::ECS::Manager& manager, MIR::Storage& storage);
        
    inline MIR::ECS::Entity::ID GetID() const
    {
        return id;
    }

private:
    const std::string IMG_PATH = "../assets/images/player_anim.png";

    const std::uint16_t INIT_WIDTH = 400;
    const std::uint16_t INIT_HEIGHT = 300;
    const std::uint16_t PROTAGONIST_WIDTH = 128;
    const std::uint16_t PROTAGONIST_HEIGHT = 128;

    const std::uint8_t MAX_ANIMATION = 3;

    const bool USING_SAVE_FILE = false;

    std::unordered_map<MIR::State, std::vector<sf::IntRect>> anim_set;
    MIR::ECS::Entity::ID id;
};