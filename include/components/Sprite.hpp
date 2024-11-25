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

#include <memory>

#include "Component.hpp"

namespace MIR
{
    struct Sprite final : public Component
    {
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        std::uint16_t width;
        std::uint16_t height;

        Sprite() : texture(nullptr), sprite(), width(0), height(0)
        {

        }

        Sprite(std::shared_ptr<sf::Texture> texture) : texture(texture), sprite(), width(0), height(0)
        {
            if (texture)
                sprite.setTexture(*texture);
        }


        Sprite(std::shared_ptr<sf::Texture> texture, std::uint16_t width, std::uint16_t height)
            : texture(texture), sprite(), width(width), height(height)
        {
            if (texture)
                sprite.setTexture(*texture);
        }
    };
}