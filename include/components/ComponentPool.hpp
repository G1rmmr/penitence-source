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

/// @file
/// @brief 풀(Pool) 기반 메모리 관리 인터페이스 및 컴포넌트 전용 풀 구현
///
/// 풀을 통해 객체를 재활용함으로써 캐시 친화성과 메모리 할당/해제에 따르는 오버헤드 감소 기대.
/// PoolBase는 풀의 기본 인터페이스를 제공하며, ComponentPool은 특정 컴포넌트 타입 T에 특화된 풀 구현.
/// Acquire 메서드를 통해 객체를 대여받고, 스마트 포인터와 커스텀 해제자를 이용해 객체 생명주기 관리.

namespace MIR
{
    /**
     * @brief 풀(Pool) 인터페이스를 위한 기본 클래스
     * 
     * 모든 풀 클래스는 이 클래스를 상속받아야 함.
     * 다양한 타입의 컴포넌트 풀을 일관성 있게 관리하기 위한 공통 타입 기준 역할 수행.
     */
    class PoolBase
    {
    public:
        /**
         * @brief 가상 소멸자
         * 
         * 상속받은 풀 클래스에서 안전한 소멸을 보장하기 위해 가상 소멸자 구현.
         */
        virtual ~PoolBase() = default;
    };

    /**
     * @brief 특정 타입 T에 대한 컴포넌트 풀 구현
     * 
     * ComponentPool은 T 타입의 컴포넌트를 재사용하기 위한 풀.
     * 최대 MAX_SIZE개의 컴포넌트를 스택(pool)에 보관할 수 있으며, 
     * Acquire 메서드를 통해 필요 시 새 컴포넌트를 생성하거나, 
     * 풀에서 재사용 가능한 컴포넌트를 팝.
     * 사용이 끝난 컴포넌트는 커스텀 해제자(Deleter)를 통해 다시 풀에 반환.
     * 
     * @tparam T 풀에서 관리할 컴포넌트 타입
     */
    template <typename T>
    class ComponentPool : public PoolBase
    {
    public:
        /**
         * @brief 풀에서 보관할 수 있는 최대 컴포넌트 수
         * 
         * 이 값은 풀에 재사용 가능한 컴포넌트를 얼마나 많이 쌓아둘 수 있는지 결정.
         * 여기서는 0xFF(255)로 설정.
         */
        static constexpr std::size_t MAX_SIZE = 0xFF;

        /**
         * @brief ComponentPool 기본 생성자
         * 
         * 초기 상태에서는 풀(stack)이 비어있음.
         */
        ComponentPool() = default;

        /**
         * @brief 풀로부터 컴포넌트를 대여(Acquire)하는 메서드
         * 
         * 템플릿 파라미터 T 타입의 컴포넌트를 반환합니다.
         * 내부적으로 풀(stack)이 비어있으면 새로 할당하고, 
         * 비어있지 않으면 스택 최상단의 재사용 가능한 컴포넌트를 가져와 
         * 새로 전달받은 인자(Args...)로 재초기화.
         * 반환 타입은 스마트 포인터(uniqe_ptr)를 이용하며, 
         * 해제 시 커스텀 해제자를 통해 컴포넌트가 다시 풀로 반환되거나 
         * 풀에 여유공간이 없으면 delete.
         * 
         * @tparam Args 컴포넌트 생성자에 전달할 파라미터 타입
         * @param args 컴포넌트 생성자에 전달할 실제 인자
         * @return 커스텀 해제자가 설정된 unique_ptr을 반환, 
         * 해제 시 풀로 반환(또는 삭제).
         */
        template <typename... Args>
        inline std::unique_ptr<Component,
            std::function<void(Component*)>> Acquire(Args&&... args)
        {
            T* component;

            if (pool.empty())
            {
                // 풀에 여유 컴포넌트가 없으므로 새로운 컴포넌트 할당
                component = new T(std::forward<Args>(args)...);
            }
            else
            {
                // 기존 컴포넌트를 재사용
                component = pool.top();
                pool.pop();

                // 새 인자로 재초기화
                *component = T(std::forward<Args>(args)...);
            }

            // 커스텀 해제자 정의: unique_ptr이 해제될 때 호출됨
            auto deleter = [this](Component* ptr)
            {
                this->Release(static_cast<T*>(ptr));
            };

            return std::unique_ptr<Component,
                std::function<void(Component*)>>(component, deleter);
        }

    private:
        /**
         * @brief 풀로 재사용할 컴포넌트를 저장하는 스택
         * 
         * 재사용 가능한 컴포넌트는 여기서 관리되며, 
         * Acquire 시 스택에서 꺼내 사용하거나,
         * 커스텀 해제자를 통해 다시 스택으로 반환.
         */
        std::stack<T*> pool;

        /**
         * @brief 커스텀 해제자 로직
         * 
         * 컴포넌트 사용이 끝나면 이 함수가 호출되어 컴포넌트를 다시 풀에 반환하거나,
         * 풀이 가득 차 있을 경우 delete.
         * 
         * @param component 반환할 컴포넌트 포인터
         */
        inline void Release(T* component)
        {
            if (component)
            {
                if (pool.size() < MAX_SIZE)
                    pool.push(component);
                else
                    delete component;
            }
        }
    };
}
