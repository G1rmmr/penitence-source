// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

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