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

#include "systems/Collision.hpp"
#include "core/ServiceLocater.hpp"
#include "events/Events.hpp"
#include "events/Announcer.hpp"

using namespace MIR;

void Collision::Update(ECSManager& manager, const float dt)
{
    auto entities = manager.Query<Position, Collider>();
    auto announcer = ServiceLocator::Instance().GetService<Announcer>();

    for(std::size_t i = 0; i < entities.size() - 1; ++i)
    {
        for(std::size_t j = i + 1; j < entities.size(); ++j)
        {
            Entity::ID vict = entities[i];
            Entity::ID prop = entities[j];

            Position* pos_a = manager.GetComponent<Position>(vict);
            Collider* box_a = manager.GetComponent<Collider>(vict);

            Position* pos_b = manager.GetComponent<Position>(prop);
            Collider* box_b = manager.GetComponent<Collider>(prop);

            if(IsColliding(pos_a, pos_b, box_a, box_b))
                announcer->PublishEvent(std::make_shared<PlayerCollided>());
        }
    }
}