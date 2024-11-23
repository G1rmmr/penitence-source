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

#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <vector>

#include "Component.hpp"

namespace MIR
{
    struct Animation final : public Component
    {
        std::vector<sf::IntRect> frames;

        float delay;
        float elapsed;

        uint8_t num_frame;
        uint8_t curr;
        uint8_t type;

        Animation() : frames(), delay(0.f), elapsed(0.f),
            num_frame(0), curr(0), type(0)
        {
            frames = std::vector<sf::IntRect>();
        } 

        Animation(const std::vector<sf::IntRect>& frames,
            float delay, float elapsed,
            uint8_t num_frame, uint8_t curr, uint8_t type)
        : frames(frames), delay(delay), elapsed(elapsed),
        num_frame(num_frame), curr(curr), type(type)
        {
            
        }
    };
}