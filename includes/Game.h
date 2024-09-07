#pragma once

#include <cstdio>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

namespace GAlpha
{
class AssetManager;
class Collider;

class Game
{
  public:
    static SDL_Renderer *renderer;
    static SDL_Event event;

    static SDL_Rect camera;

    static AssetManager assets;
    static bool is_running;

    // Screen size

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    // Set FPS
    static int FPS;
    static int FRAME_DELAY;

    enum GroupLabels : std::size_t
    {
        GROUP_MAP,
        GROUP_PLAYERS,
        GROUP_COLLIDERS,
        GROUP_PROJECTILES
    };

    Game();
    ~Game();

    void Init(const char *title, int x, int y, int w, int h, bool is_full);

    void HandleEvents();

    void Update();
    void Render();
    void Clean();

    inline bool IsRunning() const
    {
        return Game::is_running;
    }

  private:
    SDL_Window *window;
};
} // namespace GAlpha