// Created on Tue Nov 12 2024
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

#include "core/ECSManager.hpp"

using namespace G2D;

Component::Tag ECSManager::next_tag = 0;

ECSManager::~ECSManager()
{
    pools.clear();
}

Entity::ID ECSManager::CreateEntity()
{
    static Entity::ID id = next_id++;
    masks[id] = Mask();
    return id;
}

void ECSManager::DestoryEntity(Entity::ID id)
{
    masks.erase(id);

    for(auto& [tag, data] : components[id])
        components[id].erase(tag);
}