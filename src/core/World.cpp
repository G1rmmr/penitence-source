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

#include "core/World.hpp"

using namespace G2D;

void World::AddEntity(const Entity& entity)
{
    entities[last_id] = entity;
}

void World::RemoveEntity(Entity& entity)
{
    entities.erase(entity.GetID());
}

void World::Update(const float dt)
{
    for(auto& [_, sys] : systems)
    {
        for(auto& [_, entity] : entities)
            sys->Update(entity, dt);
    }
}

void World::Render()
{
    for(auto& [_, sys] : systems)
    {
        for(auto& [_, entity] : entities)
            sys->Render(entity);
    }
}