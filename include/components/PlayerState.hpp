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

#include <cstdint>

#include "Component.hpp"

namespace MIR
{
    using State = std::uint8_t;

    struct PlayerState final : public Component
    {
        enum
        {
            Idle,
            MovingLeft,
            MovingRight,
            Jumping
        };

        State now_state = PlayerState::Idle;
        bool is_jumping = false;

        PlayerState() = default;

        PlayerState(State state) : now_state(state)
        {

        }
    };
}