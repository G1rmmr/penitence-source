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
 * @brief 충돌 컴포넌트
 * 
 * 충돌 표현에 필요한 데이터 구조체.
 */

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 충돌 영역 정보를 나타내는 컴포넌트 구조체
     * 
     * 이 구조체는 오브젝트의 충돌 판정을 위한 폭(width)과 높이(height)를 관리.
     * 다른 오브젝트와의 충돌 검사 시, 이 폭과 높이를 사용하여 
     * 실제 게임 상에서의 충돌 범위 계산 가능.
     */
    struct Collider final : public Component
    {
        /**
         * @brief 충돌 영역의 폭(가로 길이)
         * 
         * 이 값은 오브젝트의 가로 방향 충돌 범위 정의.
         */
        float width;

        /**
         * @brief 충돌 영역의 높이(세로 길이)
         * 
         * 이 값은 오브젝트의 세로 방향 충돌 범위 정의.
         */
        float height;

        /**
         * @brief Collider 구조체의 기본 생성자
         * 
         * 폭과 높이를 0으로 초기화. 
         * 이 상태에서는 충돌 영역이 없는 상태와 동일.
         */
        Collider() : width(0.f), height(0.f)
        {

        }

        /**
         * @brief Collider 구조체의 폭과 높이를 지정하는 생성자
         * 
         * @param width 충돌 영역의 폭
         * @param height 충돌 영역의 높이
         * 
         * 이 생성자는 주어진 폭과 높이로 충돌 범위 설정 가능.
         */
        Collider(float width, float height) : width(width), height(height)
        {

        }
    };
}
