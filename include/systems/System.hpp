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

/**
 * @file
 * @brief 시스템 베이스 클래스
 */

#include "core/ECSManager.hpp"

namespace MIR
{
    /**
     * @brief ECS 아키텍처에서 시스템을 나타내는 추상 클래스
     *
     * System 클래스는 엔티티와 컴포넌트를 관리하는 ECS::Manager를 통해
     * 특정 로직을 수행하는 시스템의 기반 제공.
     */
    class System
    {
    public:
        /**
         * @brief 기본 생성자
         * 
         * 아무런 초기화 로직 없이 System 기반 객체 생성.
         */
        System() = default;

        /**
         * @brief 가상 소멸자
         * 
         * 파생 클래스에서 안전한 소멸을 보장하기 위해 가상 소멸자 구현.
         */
        virtual ~System() = default;
        
        /**
         * @brief 시스템 로직을 수행하는 추상 메서드
         * 
         * @param manager ECS::Manager 인스턴스 (엔티티, 컴포넌트 관리)
         * @param dt 델타 타임(초 단위)
         * 
         * 모든 구체적 시스템은 이 메서드를 구현하여 매 프레임마다 원하는 로직 수행.
         */
        virtual void Update(ECS::Manager& manager, const float dt) = 0;
    };
}
