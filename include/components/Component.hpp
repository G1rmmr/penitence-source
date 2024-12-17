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
 * @brief 컴포넌트 베이스
 * 
 * 모든 컴포넌트가 반드시 상속받아야 하는 베이스 구조체.
 */

namespace MIR
{
    /**
     * @brief 컴포넌트 수에 대한 상한값
     * 
     * 이 상수는 한 개의 엔티티가 가질 수 있는 최대 컴포넌트 수를 표현.
     * 여기서는 0xFF(255)로 설정되어 있어, 최대 255개의 컴포넌트를 
     * 한 엔티티에 할당할 수 있음을 의미.
     */
    constexpr std::uint8_t MAX_COMPONENTS = 0xFF;

    /**
     * @brief 모든 컴포넌트의 기본 클래스
     * 
     * Component는 ECS(Entity-Component-System) 아키텍처에서 엔티티가 보유할 수 있는 
     * 다양한 속성과 상태를 나타내는 추상 구조체.
     */
    struct Component
    {
        /**
         * @brief 컴포넌트를 식별하기 위한 태그 타입 정의
         * 
         * std::uint32_t 타입의 Tag를 사용하여 컴포넌트를 식별.
         * 이는 컴포넌트 관리 시스템이나 ECS 프레임워크에서 각 컴포넌트를 빠르게 
         * 조회하거나 관리할 때 활용 가능.
         */
        using Tag = std::uint32_t;
        
        /**
         * @brief 가상 소멸자
         * 
         * Component를 상속받는 모든 컴포넌트는 안전한 소멸을 위해 가상 소멸자 필요.
         * 이를 통해 파생 클래스 객체를 Component 포인터로 가리킬 때도 올바른 소멸자 호출 보장.
         */
        virtual ~Component() = default;
    };
}