// Created on Sun Nov 24 2024
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
 * @brief 애니메이션 시스템 헤더
 */

#include <unordered_map>
#include <cstdint>

#include "System.hpp"

namespace MIR
{
    /**
     * @brief 엔티티 애니메이션 상태를 업데이트하는 시스템 클래스
     *
     * Animating 시스템은 ECS::Manager로부터 애니메이션 관련 컴포넌트를 가진 엔티티를 조회하고,
     * 각 엔티티의 애니메이션 프레임, 타이밍 등을 갱신.
     */
    class Animating final : public System
    {
    public:
        /**
         * @brief Animating 시스템의 Update 메서드
         * 
         * @param manager ECS::Manager 인스턴스
         * @param dt 델타 타임(초 단위), 현재 프레임에서 지난 프레임까지의 시간 간격
         * 
         * 이 메서드는 매 프레임 호출되며, 애니메이션 컴포넌트를 가진 엔티티들을 찾아
         * elapsed 시간 증가, delay 체크, 다음 프레임 전환 등의 로직 수행.
         * 이를 통해 애니메이션이 부드럽고 일관성 있게 재생될 수 있게함.
         */
        void Update(ECS::Manager& manager, const float dt) override final;
    };
}