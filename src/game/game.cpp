#include "game/Game.hpp"

using namespace GEngine;

void Game::Init()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    circle.setRadius(50.f);
    circle.setFillColor(sf::Color::Green);

    sf::Vector2f pos = {
        WINDOW_WIDTH / 2.f - circle.getRadius(),
        WINDOW_HEIGHT / 2.f - circle.getRadius()};

    circle.setPosition(pos);
}

void Game::Update()
{
    static sf::Clock clock;
    float delta_time = clock.restart().asSeconds();
    float speed = 200.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        circle.move(0.f, -speed * delta_time);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        circle.move(0.f, speed * delta_time);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        circle.move(-speed * delta_time, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        circle.move(speed * delta_time, 0.f);
}

void Game::Run()
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        default: break;
        }
    }

    Update();
    window.clear(sf::Color::Black);

    Render();
    window.display();
}

void Game::Render()
{
    window.draw(circle);
}

void Game::Shutdown()
{
    printf("GAME OVER\n");
}