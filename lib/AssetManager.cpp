#include "AssetManager.h"

#include "ecs/Components.h"

using namespace GAlpha;

AssetManager::AssetManager(Manager* manager) : manager(manager)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateProj(
    Vector2D pos,
    Vector2D vel,
    int range,
    int speed,
    const std::string& id)
{
    auto& proj(manager->AddEntity());
    proj.AddComponent<Transform>(pos.x, pos.y, 32, 32, 1);
    proj.AddComponent<Sprite>(id, false);
    proj.AddComponent<Projectile>(range, speed);
    proj.AddComponent<Collider>("Proj");
    proj.AddGroup(Game::GROUP_PROJECTILES);
}

void AssetManager::AddTexture(const std::string& id, const char* path)
{
    textures.emplace(id, path);
}

SDL_Texture* AssetManager::GetTexture(const std::string& id)
{

}