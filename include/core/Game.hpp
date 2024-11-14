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

#include "Core.hpp"

namespace G2D
{
    class Game
    {
    public:
        inline static const std::string WINDOW_TITLE = "The Penitence";

        inline static const uint16_t WINDOW_WIDTH = 800;
        inline static const uint16_t WINDOW_HEIGHT = 600;
        
        inline static const uint16_t PROTAGONIST_WIDTH = 0x0100;
        inline static const uint16_t PROTAGONIST_HEIGHT = 0x0100;

        Game() = default;

        void Init();
        void HandleEvent();
        void Update();
        void Run();
        void Render();
        void Shutdown();

        inline bool IsRunning() const
        {
            return window->isOpen();
        }

    private:
        std::unique_ptr<sf::RenderWindow> window;
        std::unique_ptr<sf::Event> event;
        std::unique_ptr<sf::Music> music;

        std::unique_ptr<World> world;
        std::unique_ptr<ECSManager> manager;
        std::unique_ptr<Storage> storage;
    };
}