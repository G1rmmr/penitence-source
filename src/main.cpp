#include <game/Game.hpp>

int main()
{
    GEngine::Game game;
    game.Init();

    while(game.IsRunning())
        game.Run();
        
    game.Shutdown();
    return 0;
}