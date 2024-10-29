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

#include <cstdint>
#include <cassert>
#include <memory>
#include <typeindex>

#include <unordered_map>
#include <vector>

#include "Entity.hpp"
#include "systems/System.hpp"

namespace G2D
{
    class System;
    
    class World
    {
    public:
        World() = default;
        
        void Update(const float dt);
        void Render();

        void AddEntity(const Entity& entity);
        void RemoveEntity(Entity& entity);
        
        template<typename T>
        inline void AddSystem()
        {
            std::type_index type_index(typeid(T));
            assert(systems.find(type_index) == std::end(systems) && "Adding system more than once.");
            systems[type_index] = std::make_shared<T>();
        }

        template <typename T>
        inline T& GetSystem() const
        {
            auto iter = systems.find(typeid(T));
            if(iter != std::end(systems))
                return *static_cast<T*>(iter->second.get());

            throw std::runtime_error("Component not found");
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        std::unordered_map<Entity::ID, Entity> entities;
        Entity::ID last_id;
    };
}