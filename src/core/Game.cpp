// Created on Tue Oct 29 2024
// © 2024 BLACKHAND Studio. All rights reserved.

#include "core/Game.hpp"

using namespace G2D;

void Game::Init()
{
    // Window creation
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

    // Protagonist creation
    protagonist.AddComponent<Transform>();
    protagonist.AddComponent<Sprite>();
    protagonist.AddComponent<InputBehavior>();
    protagonist.AddComponent<Animation>();

    // Set protagonist transform, sprite, Animation
    Transform& transf = protagonist.GetComponent<Transform>();
    transf.pos = sf::Vector2f(PROTAGONIST_WIDTH * 0.5f, PROTAGONIST_HEIGHT * 0.5f);

    Sprite& spr = protagonist.GetComponent<Sprite>();
        sf::IntRect{0, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT};

    if(spr.texture.loadFromFile("../assets/images/player_anim.png"))
    {
        spr.sprite.setTexture(spr.texture);
        spr.sprite.setTextureRect(sf::IntRect{
            0, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});

        spr.sprite.setScale(0.5f, 0.5f);

        Animation& anim = protagonist.GetComponent<Animation>();
        anim.delay = 1.f / 6.f;
        anim.num_frame = 4;

        // Animation set.
        for(uint8_t i = 0; i < anim.num_frame; ++i)
        {
            anim.frames.emplace_back(sf::IntRect{
                i * PROTAGONIST_WIDTH, 0, PROTAGONIST_WIDTH, PROTAGONIST_HEIGHT});
        }
    }
    else
        fprintf(stderr, "TEXTURE NOT FOUND!\n");

    // Set a world;
    world.AddEntity(protagonist);

    world.AddSystem<Movement>();
    world.AddSystem<Rendering>();

    Rendering& render_sys = world.GetSystem<Rendering>();
    render_sys.SetWindow(&window);
}

void Game::HandleEvent()
{
    sf::Event event;
    InputBehavior& behavior = protagonist.GetComponent<InputBehavior>();

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::W:
                behavior.up = true;
                now_state = ProtState::Move;
                break;

            case sf::Keyboard::A:
                behavior.left = true;
                now_state = ProtState::Move;
                break;

            case sf::Keyboard::S:
                behavior.down = true;
                now_state = ProtState::Move;
                break;

            case sf::Keyboard::D:
                behavior.right = true;
                now_state = ProtState::Move;
                break;

            case sf::Keyboard::Escape:
                window.close();

            default: break;
            }
            break;

        case sf::Event::KeyReleased:
            switch(event.key.code)
            {
                case sf::Keyboard::W:
                    behavior.up = false;
                    break;
                case sf::Keyboard::A:
                    behavior.left = false;
                    break;
                case sf::Keyboard::S:
                    behavior.down = false;
                    break;
                case sf::Keyboard::D:
                    behavior.right = false;
                    break;
                default:
                    break;
            }
            if(!behavior.up && !behavior.left && !behavior.down && !behavior.right)
                now_state = ProtState::Idle;

            break;

        default: break;
        }
    }
}

void Game::Update()
{
    static sf::Clock clock;

    const float dt = clock.restart().asSeconds();
    const float speed = 200.f;

    Transform& transf = protagonist.GetComponent<Transform>();
    InputBehavior& behavior = protagonist.GetComponent<InputBehavior>();

    if(!behavior.up && !behavior.left && !behavior.down && !behavior.right)
        transf.vel = sf::Vector2f{0.f, 0.f};

    if(behavior.up) transf.vel.y = -speed;
    if(behavior.left) transf.vel.x = -speed;
    if(behavior.down) transf.vel.y = speed;
    if(behavior.right) transf.vel.x = speed;

    if(now_state == ProtState::Move)
    {
        Sprite& spr = protagonist.GetComponent<Sprite>();

        if(behavior.left)
            spr.sprite.setScale(-1.f, 1.f);

        else
            spr.sprite.setScale(1.f, 1.f);
    }

    world.Update(dt);
}

void Game::Render()
{
    world.Render();
}

void Game::Run()
{
    HandleEvent();
    Update();

    window.clear(sf::Color::Black);
    Render();
    window.display();
}

void Game::Shutdown()
{
    printf("GAME OVER\n");
}