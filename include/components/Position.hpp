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
 * @brief 위치 컴포넌트
 */

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 엔티티의 위치를 나타내는 컴포넌트 구조체
     * 
     * Position 컴포넌트는 2차원 공간 상에서 엔티티의 위치 정보 관리.
     * x, y 좌표를 통해 엔티티가 게임 월드 내 어디에 배치되는지를 지정할 수 있음.
     * 다른 시스템(렌더링, 물리 연산 등)에서 이 위치 정보를 활용해
     * 엔티티의 실제 표현이나 상호작용을 처리할 수 있음.
     */
    struct Position final : public Component
    {
        /**
         * @brief 엔티티의 x좌표
         */
        float x;

        /**
         * @brief 엔티티의 y좌표
         */
        float y;

        /**
         * @brief 기본 생성자
         * 
         * x, y를 0으로 초기화하여 엔티티는 (0,0) 위치에서 시작.
         */
        Position() : x(0.f), y(0.f)
        {
        }

        /**
         * @brief 지정한 좌표로 Position을 초기화하는 생성자
         * 
         * @param x 엔티티의 초기 x좌표
         * @param y 엔티티의 초기 y좌표
         */
        Position(float x, float y) : x(x), y(y)
        {
        }
    };
}