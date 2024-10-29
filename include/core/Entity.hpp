// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

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