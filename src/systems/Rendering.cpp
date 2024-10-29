// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#include <cassert>

#include "systems/Rendering.hpp"
#include "core/Core.hpp"

using namespace G2D;

void Rendering::Update(Entity& entity, const float dt)
{
    assert(entity.HasComponent<Animation>() && entity.HasComponent<Sprite>()
        && "To update sprite, it must has a Animation and a sprite.");

    Animation& anim = entity.GetComponent<Animation>();
    Sprite& spr = entity.GetComponent<Sprite>();

    if(anim.frames.empty())
        return;

    anim.elapsed += dt;

    if(anim.elapsed >= anim.delay)
    {
        anim.elapsed = 0.f;
        anim.curr = (anim.curr + 1) % anim.frames.size();
        spr.sprite.setTextureRect(anim.frames[anim.curr]);
    }
}

void Rendering::Render(Entity& entity)
{
    assert(entity.HasComponent<Sprite>() && entity.HasComponent<Transform>()
        && "To render entity, it must has a sprite and a transform.");

    Transform& transf = entity.GetComponent<Transform>();

    Sprite& spr = entity.GetComponent<Sprite>();
    spr.sprite.setPosition(transf.pos);

    window->draw(spr.sprite);
}

void Rendering::SetWindow(sf::RenderWindow* r_window)
{
    window = r_window;
}