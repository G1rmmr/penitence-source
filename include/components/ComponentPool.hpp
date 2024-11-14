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
    class PoolBase
    {
    public:
        virtual ~PoolBase() = default;
    };

    template <typename T>
    class ComponentPool : public PoolBase, public std::enable_shared_from_this<ComponentPool<T>>
    {
    public:
        static constexpr std::size_t MAX_SIZE = 0x80;

        ComponentPool()
        {
            for (std::size_t i = 0; i < MAX_SIZE; ++i)
                pool.push(std::make_unique<T>());
        }

        template <typename... Args>
        inline std::shared_ptr<T> Acquire(Args&&... args)
        {
            if (pool.empty())
                return std::make_shared<T>(std::forward<Args>(args)...);

            auto component = std::move(pool.top());
            pool.pop();

            std::weak_ptr<ComponentPool<T>> self = this->shared_from_this();

            return std::shared_ptr<T>(component.release(),
                [self](T* comp)
                {
                    if (auto pool = self.lock())
                        pool->Release(comp);
                    else
                        delete comp;
                });
        }

    private:
        inline void Release(T* component)
        {
            if(component)
            {
                if(pool.size() < MAX_SIZE)
                    pool.push(std::unique_ptr<T>(component));
                else
                    delete component;
            }
        }
        std::stack<std::unique_ptr<T>> pool;
    };
}