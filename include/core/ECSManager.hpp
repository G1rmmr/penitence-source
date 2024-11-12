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

#include "Entity.hpp"
#include "components/Component.hpp"
#include "components/ComponentPool.hpp"

namespace G2D
{
    using Mask = std::bitset<MAX_COMPONENTS>;
    using Data = std::unordered_map<Component::Tag, std::shared_ptr<Component>>;
    using Pool = std::unique_ptr<ComponentPool<Component>>;

    class ECSManager
    {
    public:
        ECSManager() = default;

        Entity::ID CreateEntity();
        void DestoryEntity(Entity::ID id);

        template <typename T, typename... Args>
        inline void AddComponent(Entity::ID id, Args&&... args)
        {
            Component::Tag tag = GetTag<T>();
            if(masks[id][tag])
                return;
            
            masks[id].set(tag);

            if(pools.find(tag) == pools.end())
                pools[tag] = std::make_unique<ComponentPool<T>>();

            auto& pool = static_cast<ComponentPool<T>&>(*pools[tag]);
            auto component = pool.Acquire(std::forward<Args>(args)...);
            components[id][tag] = component;
        }

        template <typename T>
        inline std::shared_ptr<T> GetComponent(Entity::ID id)
        {
            Component::Tag tag = GetTag<T>();
            if(!masks[id][tag])
                return nullptr;

            Data dictionary = components[id];

            if(dictionary.find(tag) != dictionary.end())
                return std::static_pointer_cast<T>(dictionary[tag]);

            return nullptr;
        }

        template <typename... Components>
        inline std::vector<Entity::ID> Query() const
        {
            std::vector<Entity::ID> result;

            for(const auto& [id, mask] : masks)
                if(mask.test(GetTag<Components>(), ...))
                    result.emplace_back(id);

            return result;
        }

    private:
        std::unordered_map<Entity::ID, Data> components;
        std::unordered_map<Entity::ID, Mask> masks;

        std::unordered_map<Component::Tag, Pool> pools;
        
        Entity::ID next_id;
        Component::Tag next_tag = 0;

        static Entity::ID GetID();
        
        template <typename T>
        static Component::Tag GetTag()
        {
            static Component::Tag tag = next_tag++;
            return tag;
        }
    };
}