// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

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