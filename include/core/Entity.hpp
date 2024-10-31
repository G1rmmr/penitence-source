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
#include <stdexcept>

#include "components/Component.hpp"

namespace G2D
{
    class Entity
    {
    public:
        using ID = uint16_t;

        Entity() = default;

        Entity(ID id) : id(id)
        {

        }

        Entity& operator=(const Entity& other)
        {
            if(this != &other)
            {
                this->components = other.components;
                this->id = other.id;
            }
            
            return *this;
        }

        inline const ID GetID() const
        {
            return id;
        }

        template <typename T>
        inline bool HasComponent() const
        {
            return components.find(typeid(T)) != std::end(components);
        }

        template <typename T, typename... Args>
        inline void AddComponent(Args&&... args)
        {
            assert(!HasComponent<T>() && "Entity already has this component type.");
            components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        inline void RemoveComponent()
        {
            auto iter = components.find(typeid(T));
            if(iter != std::end(components))
                components.erase(iter);
        }

        template <typename T>
        inline T& GetComponent() const
        {
            auto iter = components.find(typeid(T));
            if(iter != std::end(components))
                return *static_cast<T*>(iter->second.get());

            throw std::runtime_error("Component not found");
        }
        
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
        ID id;
    };
}