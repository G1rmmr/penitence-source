// Created on Tue Nov 26 2024
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
 * @brief 플레이어 충돌 이벤트
 * 
 */

#include "Event.hpp"
#include "core/Entity.hpp"

namespace MIR
{
    /**
     * @brief 플레이어 충돌 발생 시점을 나타내는 이벤트 구조체
     *
     * PlayerCollided 이벤트는 플레이어가 어떤 대상과 충돌했을 때 발생하는 이벤트 타입.
     * 이를 이용해 충돌 처리에 대한 다양한 로직 구현 가능.
     */
    struct PlayerCollided : public Event
    {
        /**
         * @brief PlayerCollided 이벤트 생성자
         * 
         * 이벤트 타입을 CollisionHit으로 설정하여 플레이어 충돌 이벤트임을 명시.
         */
        PlayerCollided() : Event(EventType::CollisionHit)
        {

        }
    };
}
