// Created on Sat Nov 30 2024
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
 * @brief 중력 컴포넌트
 * 
 * 중력 데이터 포함.
 */

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 중력 가속도 상수 (m/s² 단위)
     */
    const float GRAV_ACCEL = 9.8f;

    /**
     * @brief 엔티티에 중력 특성을 부여하는 컴포넌트
     * 
     * Gravity 컴포넌트는 엔티티가 중력의 영향을 받아 낙하하거나 
     * 공중 상태에 있을 때 적용할 물리 연산을 위한 기초 정보를 담고 있음.
     */
    struct Gravity final : public Component
    {
        /**
         * @brief 엔티티의 무게(질량에 비례하는 값)
         * 
         * 이 값은 중력 영향 하에서 엔티티가 낙하할 때 속도를 결정하는데 참고 가능.
         */
        float weight = 1.f;

        /**
         * @brief 엔티티가 공중에 있는지 여부
         * 
         * true일 경우 엔티티는 지면에 닿아있지 않은 상태(점프 중, 낙하 중 등)이며,
         * 중력으로 인한 낙하 계산 수행.
         * 
         * false일 경우 지면에 서있거나, 더 이상 낙하나 상승이 필요 없는 상태로 간주할 수 있습니다.
         */
        bool in_air = false;

        /**
         * @brief 지정된 무게와 공중 상태로 Gravity 컴포넌트를 초기화하는 생성자
         * 
         * @param weight 엔티티의 무게
         * @param in_air 엔티티가 공중에 있는지 여부
         */
        Gravity(float weight, bool in_air)
            : weight(weight), in_air(in_air)
        {
        }
    };
}