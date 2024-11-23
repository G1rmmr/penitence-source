// Created on Fri Nov 22 2024
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

#include <SFML/Window.hpp>

#include "Event.hpp"

namespace G2D
{
    enum class Key
    {
        W = sf::Keyboard::W,
        A = sf::Keyboard::A,
        S = sf::Keyboard::S,
        D = sf::Keyboard::D,
        ESC = sf::Keyboard::Escape
    };

    struct Keyboard : public Event
    {
        Key code;
        bool is_pressed = false;

        Keyboard(Key code, bool pressed) : code(code), is_pressed(pressed)
        {

        }
    };
}