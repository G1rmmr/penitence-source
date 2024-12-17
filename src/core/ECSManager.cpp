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

using namespace MIR;
using namespace ECS;

Manager::~Manager()
{
    components.clear();
    masks.clear();
    pools.clear();
}

Entity::ID Manager::CreateEntity()
{
    Entity::ID id = -1;
    
    if(!id_queue.empty())
    {
        id = id_queue.front();
        id_queue.pop();
    }
    else
        id = next_id++;

    if (masks.find(id) != masks.end())
        throw std::runtime_error("Entity ID already in use");
    
    masks[id] = Mask();
    components[id] = Data();
    return id;
}

void Manager::DestoryEntity(Entity::ID id)
{
    if (masks.find(id) == masks.end())
        return;

    masks.erase(id);
    components.erase(id);
    id_queue.push(id);
}
