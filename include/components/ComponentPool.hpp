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
#include <memory>
#include <stack>
#include <functional>
#include <stdexcept>

namespace G2D
{
    class PoolBase
    {
    public:
        virtual ~PoolBase() = default;
    };

    template <typename T>
    class ComponentPool : public PoolBase
    {
    public:
        static constexpr std::size_t MAX_SIZE = 0xFF;

        ComponentPool() = default;

        template <typename... Args>
        inline std::unique_ptr<Component,
            std::function<void(Component*)>> Acquire(Args&&... args)
        {
            T* component;

            if (pool.empty())
                component = new T(std::forward<Args>(args)...);
            else
            {
                component = pool.top();
                pool.pop();

                *component = T(std::forward<Args>(args)...);
            }

            auto deleter = [this](Component* ptr)
            {
                this->Release(static_cast<T*>(ptr));
            };

            return std::unique_ptr<Component,
                std::function<void(Component*)>>(component, deleter);
        }

    private:
        std::stack<T*> pool;

        inline void Release(T* component)
        {
            if(component)
            {
                if(pool.size() < MAX_SIZE)
                    pool.push(component);
                else
                    delete component;
            }
        }
    };
}