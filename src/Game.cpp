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

Game::Game()
{
    window = std::make_unique<sf::RenderWindow>();
    event = std::make_unique<sf::Event>();
    music = std::make_unique<sf::Music>();
    world = std::make_unique<World>();
    manager = std::make_unique<ECSManager>();
    storage = std::make_unique<Storage>(SAVE_PATH);
}

Game::~Game()
{

}

void Game::Init()
{
    std::shared_ptr<Dispatcher> dispatcher = std::make_shared<Dispatcher>();
    std::shared_ptr<Announcer> announcer = std::make_shared<Announcer>();

    ServiceLocator::Instance().RegisterService(dispatcher);
    ServiceLocator::Instance().RegisterService(announcer);

    window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    // Entities set
    std::unique_ptr<Protagonist> protagonist = std::make_unique<Protagonist>();
    protagonist->Init(*manager, *storage);
    Entity::ID prot_id = protagonist->GetID();

    Entity::ID wall = manager->CreateEntity();
    manager->AddComponent<Position>(wall, 700, -100);
    manager->AddComponent<Collider>(wall, 100, 1000);

    // Set a world;
    world->AddSystem<Movement>();
    world->AddSystem<Rendering>();
    world->AddSystem<Animating>();
    world->AddSystem<Collision>();

    dispatcher->AddListener(EventType::KeyInput,
        [&](const std::shared_ptr<Event>& event)
        {
            auto key = std::static_pointer_cast<Keyboard>(event);
            PlayerState* prot_state = manager->GetComponent<PlayerState>(prot_id);

            if(key->is_pressed)
            {
                switch(key->code)
                {
                case Key::A:
                    prot_state->now_state = PlayerState::MovingLeft;
                    break;

                case Key::D:
                    prot_state->now_state = PlayerState::MovingRight;
                    break;

                case Key::W:
                    prot_state->now_state = PlayerState::Jumping;
                    break;

                case Key::ESC:
                    window->close();
                    break;

                default: break;
                }
            }
            else
            {
                switch(key->code)
                {
                case Key::A:
                case Key::D:
                    prot_state->now_state = PlayerState::Idle;
                    break;

                default: break;
                }
            }
        });

    dispatcher->AddListener(EventType::CollisionHit,
        [&](const std::shared_ptr<Event>& event)
        {
            PlayerState* prot_state = manager->GetComponent<PlayerState>(prot_id);
            prot_state->now_state = PlayerState::Idle;
        });

    // Set Music
    if(!music->openFromFile("../assets/audios/Penitence.wav"))
        return;

    music->play();
    music->setLoop(true);
}

void Game::HandleEvent()
{
    auto announcer = ServiceLocator::Instance().GetService<Announcer>();
    auto dispatcher = ServiceLocator::Instance().GetService<Dispatcher>();

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