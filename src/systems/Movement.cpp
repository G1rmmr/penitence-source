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

#include <cassert>

#include "systems/Movement.hpp"
#include "components/Components.hpp"

using namespace G2D;

void Movement::Update(ECSManager& manager, const float dt)
{
    std::vector<Entity::ID> entities = manager.Query<Position, Velocity>();

    for(const auto& id : entities)
    {
        std::shared_ptr<Position> pos = manager.GetComponent<Position>(id);
        std::shared_ptr<Velocity> vel = manager.GetComponent<Velocity>(id);

        pos->x += vel->x * dt;
        pos->y += vel->y * dt;
    }
}