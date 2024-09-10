#include "AssetManager.h"

#include "ecs/Components.h"

using namespace GAlpha;

AssetManager::AssetManager(Manager& manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
    for (auto &[_, tex] : textures)
        SDL_DestroyTexture(tex);
}

void AssetManager::CreateProj(const std::string &id, Vector2D pos, Vector2D vel, int range, int speed)
{
    auto &proj(manager.AddEntity());
    proj.AddComponent<Transform>(pos.x, pos.y, 32, 32, 1);
    proj.AddComponent<Sprite>(id, false);
    proj.AddComponent<Projectile>(vel, range, speed);
    proj.AddComponent<Collider>("Proj");
    proj.AddGroup(Game::GROUP_PROJECTILES);
}

void AssetManager::AddTexture(const std::string &id, const char *path)
{
    textures.emplace(id, TextureManager::Load(path));
}

SDL_Texture *AssetManager::GetTexture(const std::string &id)
{
    return textures[id];
}