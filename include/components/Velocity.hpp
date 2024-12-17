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
 * @brief 속도 컴포넌트
 * 
 * 속도 데이터 포함.
 */

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 엔티티의 속도(velocity) 정보를 담는 컴포넌트 구조체
     * 
     * Velocity 컴포넌트는 엔티티가 움직이는 방향과 속도를 나타내는 (x, y) 벡터 제공.
     */
    struct Velocity final : public Component
    {
        /**
         * @brief 가로(x) 방향 속도
         */
        float x;

        /**
         * @brief 세로(y) 방향 속도
         */
        float y;

        /**
         * @brief 기본 생성자
         */
        Velocity() : x(0.f), y(0.f)
        {            
        }

        /**
         * @brief 지정한 속도로 초기화하는 생성자
         * 
         * @param x 초기 x 방향 속도
         * @param y 초기 y 방향 속도
         * 
         * 이 생성자를 통해 엔티티가 초기부터 특정 방향으로 이동하는 상태 설정 가능.
         */
        Velocity(float x, float y) : x(x), y(y)
        {            
        }
    };
}
