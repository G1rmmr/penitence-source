// Created on Fri Nov 22 2024
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
 * @brief 이벤트 베이스 클래스 헤더
 * 
 * 이벤트 타입을 정의하는 클래스.
 */

namespace MIR
{
    /**
     * @brief 이벤트 유형을 나타내는 열거형
     *
     * 게임 내에서 발생하는 다양한 이벤트를 구분하기 위한 타입.
     */
    enum class EventType
    {
        KeyInput,      ///< 키 입력 관련 이벤트
        CollisionHit   ///< 충돌 발생 관련 이벤트
    };

    /**
     * @brief 모든 이벤트의 기본 구조체
     *
     * Event 구조체는 특정 EventType을 담고 있으며,
     * 이를 상속받아 다양한 구체적 이벤트 확장 가능.
     * @note type 멤버를 통해 이벤트 핸들러나 Dispatcher는 이벤트 종류를 판별하고 알맞은 처리 로직을 적용.
     */
    struct Event
    {
        /**
         * @brief 소멸자 (가상 소멸자로 선언)
         *
         * 파생 클래스에서 안전한 소멸을 보장하기 위해 가상 소멸자 제공.
         */
        virtual ~Event() = default;

        /**
         * @brief 이벤트 타입을 나타내는 멤버 변수
         *
         * 이 값을 통해 이벤트 핸들러는 이벤트 종류를 식별하고,
         * 해당 이벤트에 맞는 처리 로직 수행.
         */
        EventType type;

        /**
         * @brief Event 구조체의 생성자
         * 
         * @param type 생성 시 지정할 이벤트 타입
         *
         * 이 생성자를 통해 이벤트 타입을 지정할 수 있으며,
         * 파생 클래스에서는 추가적인 이벤트 정보 확장 가능.
         */
        Event(EventType type) : type(type)
        {
        }
    };
}