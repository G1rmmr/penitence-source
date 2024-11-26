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

#pragma once

#include <memory>
#include <vector>

#include "ECSManager.hpp"

#include "components/Components.hpp"
#include "systems/Systems.hpp"

namespace MIR
{   
    class World
    {
    public:
        World() = default;
        
        void Update(ECSManager& manager, const float dt);
        void Render(ECSManager& manager, sf::RenderWindow& window);
        
        template<typename T>
        inline void AddSystem()
        {
            std::unique_ptr<T> system = std::make_unique<T>();
            systems.emplace_back(std::move(system));
        }

    private:
        std::vector<std::unique_ptr<System>> systems;

        template<typename T>
        inline T* GetSystem()
        {
            for(const auto& sys : systems)
            {
                T* target = dynamic_cast<T*>(sys.get());
                if (target)
                    return target;
            }
            return nullptr;
        }
    };
}