// Created on Tue Nov 26 2024
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

#include "System.hpp"
#include "components/Collider.hpp"
#include "components/Position.hpp"

namespace MIR
{
    class Collision final : public System
    {
    public:
        void Update(ECSManager& manager, const float dt) override final;

    private:
        inline bool IsColliding(
            const Position* left_pos,
            const Position* right_pos,
            const Collider* left_box,
            const Collider* right_box) const
        {
            return (left_pos->x < right_pos->x + right_box->width
                && left_pos->x + left_box->width > right_pos->x
                && left_pos->y < right_pos->y + right_box->height
                && left_pos->y + left_box->height > right_pos->y);
        }
    };
}