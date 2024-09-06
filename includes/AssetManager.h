#pragma once

#include <unordered_map>
#include <string>

#include "TextureManager.h"
#include "Vector2D.h"

#include "ecs/ECS.h"

namespace GAlpha
{
    class AssetManager
    {
    public:
        AssetManager(Manager* manager);
        ~AssetManager();

        void CreateProj(
            Vector2D pos,
            Vector2D vel,
            int range,
            int speed,
            const std::string& id);

        // Texture management
        void AddTexture(const std::string& id, const char* path);
        SDL_Texture* GetTexture(const std::string& id);

    private:
        std::unordered_map<std::string, SDL_Texture*> textures;
        Manager* manager;
    };
}