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

#include "core/Game.hpp"

using namespace G2D;

void Game::Init()
{
    bool use_save = false;

    window = std::make_unique<sf::RenderWindow>();
    event = std::make_unique<sf::Event>();
    music = std::make_unique<sf::Music>();
    world = std::make_unique<World>();
    manager = std::make_unique<ECSManager>();

    // Window creation
    window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    Entity::ID protagonist = manager->CreateEntity();

    if(use_save)
    {
        world->Load(*manager);
    }
    else
    {
        Position pos;
        pos.x = WINDOW_WIDTH * 0.5f;
        pos.y = WINDOW_HEIGHT * 0.5f;
        manager->AddComponent<Position>(protagonist, std::move(pos));
    }

    // Protagonist creation
    Sprite spr;
    spr.texture = std::make_unique<sf::Texture>();
    spr.sprite = std::make_unique<sf::Sprite>();

    if(spr.texture->loadFromFile("../assets/images/player_anim.png"))
    {
        spr.sprite->setTexture(*(spr.texture));
        
        std::shared_ptr<Position> pos = manager->GetComponent<Position>(protagonist);
        spr.sprite->setPosition(pos->x, pos->y);
        spr.sprite->setScale(0.5f, 0.5f);

        spr.sprite->setTextureRect(sf::IntRect{
            0, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});

        manager->AddComponent<Sprite>(protagonist, std::move(spr));

        Animation anim;
        anim.delay = 1.f / 6.f;
        anim.num_frame = 4;

        // Animation set.
        for(uint8_t i = 0; i < anim.num_frame; ++i)
        {
            anim.frames.emplace_back(sf::IntRect{
                i * PROTAGONIST_WIDTH, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});
        }
        manager->AddComponent<Animation>(protagonist, std::move(anim));
    }
    else
        fprintf(stderr, "TEXTURE NOT FOUND!\n");

    // Set a world;
    world->AddSystem<Movement>();
    world->AddSystem<Rendering>();

    // Set Music
    if(!music->openFromFile("../assets/audios/Penitence.wav"))
        return;

    music->play();
    music->setLoop(true);
}

void Game::HandleEvent()
{
    while(window->pollEvent(*event))
    {
        switch(event->type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            switch(event->key.code)
            {
            case sf::Keyboard::Escape:
                window->close();
                break;
            
            default: break;
            }
        default: break;
        }
    }
}

void Game::Update()
{
    static sf::Clock clock;

    const float dt = clock.restart().asSeconds();
    const float speed = 200.f;

    world->Update(*manager, dt);
}

void Game::Render()
{
    world->Render(*manager, *window);
}

void Game::Run()
{
    HandleEvent();
    Update();

    window->clear(sf::Color::Black);
    Render();
    window->display();
}

void Game::Shutdown()
{
    printf("GAME OVER\n");
    world->Save(*manager);
}