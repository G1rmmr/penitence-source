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

#include "Game.hpp"

using namespace MIR;

void Game::Init()
{
    SetManagers();
    window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    std::unique_ptr<Protagonist> protagonist = std::make_unique<Protagonist>();
    protagonist->Init(*manager, *storage);

    Entity::ID prot_id = protagonist->GetID();

    // Set a world;
    world->AddSystem<Movement>();
    world->AddSystem<Rendering>();

    dispatcher->AddListener(EventType::KeyInput,
        [&](const std::shared_ptr<Event>& event)
        {
            auto key = std::static_pointer_cast<Keyboard>(event);
            Velocity* vel = manager->GetComponent<Velocity>(prot_id);

            switch(key->code)
            {
            case Key::A:
                vel->x = key->is_pressed ? -200.f : 0.f;
                break;

            case Key::D:
                vel->x = key->is_pressed ? 200.f : 0.f;
                break;

            case Key::ESC:
                if(key->is_pressed)
                    window->close();

                break;

            default: break;
            }
        });

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
        if(event->type == sf::Event::Closed)
            window->close();

        else if(event->type == sf::Event::KeyPressed)
        {
            Key code = static_cast<Key>(event->key.code);
            announcer->PublishEvent(std::make_shared<Keyboard>(code, true));
        }

        else if(event->type == sf::Event::KeyReleased)
        {
            Key code = static_cast<Key>(event->key.code);
            announcer->PublishEvent(std::make_shared<Keyboard>(code, false));
        }
    }
    announcer->ProcessEvents(*dispatcher);
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

    sf::Color gray{0x7f, 0x7f, 0x7f};
    window->clear(gray);

    Render();
    window->display();
}

void Game::Shutdown()
{
    printf("GAME OVER\n");
    storage->Save(*manager);
}