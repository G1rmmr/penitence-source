// Created on Fri Nov 08 2024
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

#include <cstdint>
#include <stack>
#include <memory>

namespace G2D
{
    template <typename T>
    class ComponentPool
    {
    public:
        static constexpr std::size_t MAX_SIZE = 0x80;
        
        ComponentPool()
        {
            for (std::size_t i = 0; i < MAX_SIZE; ++i)
                pool.push(std::make_unique<T>());
        }

        std::shared_ptr<T> Acquire()
        {
            if (pool.empty())
                return nullptr_t;

            auto component = std::move(pool.top());
            pool.pop();

            return std::make_shared<T>(component.Release(),
                [this](T* comp)
                {
                    this->Release(comp);
                });
        }

    private:
        void Release(T* component)
        {
            if(pool.size() < MAX_SIZE)
                pool.push(std::unique_ptr<T>(component));
            else
                delete component;
        }
        std::stack<std::unique_ptr<T>> pool;
    };
}