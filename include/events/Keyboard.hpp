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
 * @brief 키보드 이벤트 헤더
 * 
 * 키보드와 관련된 이벤트 처리 기능 수행.
 */

#include <SFML/Window.hpp>
#include "Event.hpp"

namespace MIR
{
    /**
     * @brief 게임 내 키보드 키 식별을 위한 열거형
     * 
     * SFML 키 코드를 기반으로 게임 내에서 사용할 키를 정의.
     * - W, A, S, D: 방향 이동에 자주 사용되는 키
     * - ESC: 게임 메뉴나 종료 동작에 사용
     */
    enum class Key
    {
        W = sf::Keyboard::W,
        A = sf::Keyboard::A,
        S = sf::Keyboard::S,
        D = sf::Keyboard::D,
        ESC = sf::Keyboard::Escape
    };

    /**
     * @brief 키보드 입력 이벤트를 나타내는 구조체
     * 
     * 특정 키보드 키가 눌리거나 떼어지는(KeyInput) 시점에 발생하는 이벤트 표현.
     * 이 이벤트를 통해 게임 로직은 어떤 키가 눌렸는지, 언제 해제되었는지 등을 파악.
     */
    struct Keyboard : public Event
    {
        /**
         * @brief 발생한 키보드 입력에 해당하는 키 코드
         * 
         * Key 열거형으로 정의된 특정 키를 나타내며, 
         * 이 값을 통해 게임 로직은 어떤 키가 입력되었는지 식별.
         */
        Key code;

        /**
         * @brief 키가 눌렸는지(is_pressed = true) 아니면 해제되었는지(false) 여부
         * 
         * true일 경우 키가 눌린 상태, false일 경우 키가 해제된 상태 의미.
         * 이를 통해 게임 내에서 키 입력 상태 변화에 따른 로직 분기 가능.
         */
        bool is_pressed = false;

        /**
         * @brief Keyboard 이벤트 생성자
         * 
         * @param code 발생한 키보드 키 코드
         * @param pressed 키가 눌린 상태인지 아닌지를 나타내는 불리언 값
         * 
         * EventType::KeyInput 타입의 이벤트로 초기화하며,
         * 발생한 키보드 입력 정보 설정.
         */
        Keyboard(Key code, bool pressed)
            : Event(EventType::KeyInput)
            , code(code), is_pressed(pressed)
        {

        }
    };
}
