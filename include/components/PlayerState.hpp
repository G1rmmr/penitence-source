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
 * @brief 플레이어 상태 컴포넌트 헤더
 * 
 * 플레이어의 상태 데이터.
 */

#include <cstdint>

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 플레이어 상태를 표현하는 정수형 타입
     *
     * State는 플레이어의 현재 상태를 나타내는 정수형 별칭.
     * PlayerState 구조체 내부에서 정의한 상수를 사용하여 플레이어가 어떤 상태인지 구분할 수 있습니다.
     */
    using State = std::uint8_t;

    /**
     * @brief 플레이어 상태를 관리하는 컴포넌트 구조체
     * 
     * PlayerState는 플레이어 캐릭터의 현재 상태를 추적.
     * 
     * 게임 로직에서 이 컴포넌트를 활용하여 플레이어 동작을 결정하거나 
     * 애니메이션 전환 등에 반영 가능.
     */
    struct PlayerState final : public Component
    {
        /**
         * @brief 플레이어 상태에 대한 열거형 상수
         * 
         * - Idle: 플레이어가 정지 상태일 때  
         * - MovingLeft: 플레이어가 왼쪽으로 이동 중일 때  
         * - MovingRight: 플레이어가 오른쪽으로 이동 중일 때  
         * - Jumping: 플레이어가 점프 중일 때
         */
        enum
        {
            Idle,        ///< 플레이어가 정지 상태
            MovingLeft,  ///< 플레이어가 왼쪽으로 이동 중
            MovingRight, ///< 플레이어가 오른쪽으로 이동 중
            Jumping      ///< 플레이어가 점프 중
        };

        /**
         * @brief 플레이어의 현재 상태
         * 
         * 기본값은 Idle(정지 상태).
         * 이 값을 변경함으로써 플레이어 동작 로직 제어 가능.
         */
        State now_state = PlayerState::Idle;

        /**
         * @brief 플레이어가 점프 중인지 여부
         * 
         * true일 경우 플레이어는 점프 중이며, 
         * 게임 로직에서 중력 적용, 점프 애니메이션 전환 등이 수행될 수 있음.
         */
        bool is_jumping = false;

        /**
         * @brief PlayerState의 기본 생성자
         * 
         * now_state를 Idle로, is_jumping을 false로 두어 플레이어는 정지 상태로 시작.
         */
        PlayerState() = default;

        /**
         * @brief 지정한 상태로 PlayerState를 초기화하는 생성자
         * 
         * @param state 플레이어의 초기 상태
         * 
         * 이 생성자를 통해 플레이어 상태를 Idle 이외의 다른 상태로 초기화 가능.
         */
        PlayerState(State state) : now_state(state)
        {
        }
    };
}