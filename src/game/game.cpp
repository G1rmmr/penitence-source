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