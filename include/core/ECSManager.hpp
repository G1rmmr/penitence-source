// Created on Fri Nov 08 2024
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

#include <unordered_map>
#include <vector>
#include <bitset>
#include <memory>
#include <concepts>
#include <queue>

#include "Entity.hpp"
#include "components/Component.hpp"
#include "components/ComponentPool.hpp"

namespace MIR
{
    using Mask = std::bitset<MAX_COMPONENTS>;

    using Data = std::unordered_map<Component::Tag,
        std::unique_ptr<Component, std::function<void(Component*)>>>;

    using Pool = std::shared_ptr<PoolBase>;

    class ECSManager
    {
    public:
        ECSManager() = default;
        ~ECSManager();

        Entity::ID CreateEntity();
        void DestoryEntity(Entity::ID id);

        template <typename T, typename... Args>
        requires std::constructible_from<T, Args...>
        inline void AddComponent(Entity::ID id, Args&&... args)
        {
            if (masks.find(id) == masks.end())
                throw std::runtime_error("Invalid Entity ID");

            Component::Tag tag = GetTag<T>();
            if (masks[id][tag])
                throw std::runtime_error("Component already exists for this Entity");
            
            masks[id].set(tag);

            if(pools.find(tag) == pools.end())
                pools[tag] = std::make_shared<ComponentPool<T>>();

            auto pool = std::static_pointer_cast<ComponentPool<T>>(pools[tag]);
            auto component = pool->Acquire(std::forward<Args>(args)...);
            components[id][tag] = std::move(component);
        }

        template <typename T>
        inline T* GetComponent(Entity::ID id)
        {
            Component::Tag tag = GetTag<T>();
            if(!masks[id][tag])
                return nullptr;

            auto it = components.find(id);

            if(it != components.end() && it->second.find(tag) != it->second.end())
                return static_cast<T*>(it->second[tag].get());

            return nullptr;
        }

        template <typename T>
        inline bool HasComponent(Entity::ID id)
        {
            Component::Tag tag = GetTag<T>();
            return masks[id][tag];
        }

        template <typename... Components>
        inline std::vector<Entity::ID> Query() const
        {
            std::vector<Entity::ID> result;

            for(const auto& [id, mask] : masks)
                if((mask.test(GetTag<Components>()) && ...))
                    result.emplace_back(id);

            return result;
        }

    private:
        std::unordered_map<Entity::ID, Data> components;
        std::unordered_map<Entity::ID, Mask> masks;
        std::unordered_map<Component::Tag, Pool> pools;

        std::queue<Entity::ID> id_queue;
        
        inline static Entity::ID next_id = 0;
        inline static Component::Tag next_tag;

        inline Entity::ID GetID()
        {
            return next_id++;
        }
        
        template <typename T>
        inline static Component::Tag GetTag()
        {
            static Component::Tag tag = next_tag++;
            return tag;
        }
    };
}