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
 * @brief 이동 시스템 헤더
 */

#include "System.hpp"

namespace MIR
{
    /**
     * @brief 엔티티 이동 로직을 담당하는 시스템 클래스
     * 
     * Movement 시스템은 ECS::Manager를 통해 위치(Position), 속도(Velocity) 등의 컴포넌트를 가진 
     * 엔티티를 찾아 매 프레임마다 dt(델타 타임)를 고려하여 위치 갱신.
     */
    class Movement final : public System
    {
    public:
        /**
         * @brief Movement 시스템의 Update 메서드
         * 
         * @param manager ECS::Manager 인스턴스 (엔티티와 컴포넌트 관리)
         * @param dt 델타 타임(초 단위)
         * 
         * 이 메서드는 매 프레임 호출되며, 이동 관련 컴포넌트를 가진 엔티티를 찾은 뒤
         * 속도*dt를 현재 위치에 반영하여 엔티티의 새로운 위치 계산.
         */
        void Update(ECS::Manager& manager, const float dt) override final;
    };
}
