#pragma once

#include <string>
#include <unordered_map>

#include "ecs/ECS.h"

#include "TextureManager.h"
#include "Vector2D.h"

namespace GAlpha
{
class AssetManager
{
  public:
    AssetManager(const Manager &manager);
    ~AssetManager();

    void CreateProj(const std::string &id, Vector2D pos, Vector2D vel, int range, int speed);

    // Texture management
    void AddTexture(const std::string &id, const char *path);
    SDL_Texture *GetTexture(const std::string &id);

  private:
    std::unordered_map<std::string, SDL_Texture *> textures;
    Manager manager;
};
} // namespace GAlpha