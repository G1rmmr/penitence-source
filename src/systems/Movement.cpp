// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#include <cassert>

#include "systems/Movement.hpp"
#include "core/Core.hpp"

using namespace G2D;

void Movement::Update(Entity& entity, const float dt)
{
    assert(entity.HasComponent<Transform>() && "To move entity, it must has a position.");

    Transform& transf = entity.GetComponent<Transform>();
    transf.pos.x += dt * transf.vel.x;
    transf.pos.y += dt * transf.vel.y;
}