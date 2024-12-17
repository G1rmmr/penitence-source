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

#include <cstdint>

/**
 * @file
 * @brief 엔티티(ID) 정의를 물리적으로 분리한 헤더
 * 
 * Entity ID에 대한 정보 포함.
 */

namespace MIR
{
    namespace ECS
    {
        /**
         * @brief ECS(Entity-Component-System) 아키텍처에서 엔티티를 식별하기 위한 구조체
         *
         * Entity는 게임 세계를 구성하는 기본 객체의 식별자를 제공하는 단순 구조체.
         * 엔티티는 컴포넌트를 부착하여 다양한 특성과 행동을 가질 수 있음.
         */
        struct Entity
        {
            /**
             * @brief 엔티티를 식별하기 위한 정수형 타입 별칭
             *
             * 엔티티마다 고유 ID를 부여하여, 엔티티 관리.
             * uint16_t를 사용하여 최대 65,535개의 엔티티 식별 가능(상황에 따라 조정 가능).
             */
            using ID = uint16_t;
        };
    }
}
