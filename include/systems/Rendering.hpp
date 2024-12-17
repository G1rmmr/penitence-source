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
 * @brief 렌더링 시스템 헤더
 */

#include "System.hpp"

namespace MIR
{
    /**
     * @brief 엔티티의 그래픽 렌더링을 담당하는 시스템 클래스
     * 
     * Rendering 시스템은 ECS::Manager로부터 스프라이트, 위치, 애니메이션 등 
     * 렌더링에 필요한 컴포넌트를 가진 엔티티를 찾아 매 프레임마다 화면에 그림.
     * Update 메서드에서 렌더링 대상 상태를 준비한 뒤, Render 메서드에서 
     * SFML RenderWindow를 통해 실제 그래픽 표현.
     */
    class Rendering final : public System
    {
    public:
        /**
         * @brief 렌더링을 위한 사전 준비 작업을 수행하는 Update 메서드
         * 
         * @param manager ECS::Manager 인스턴스
         * @param dt 델타 타임(초 단위)
         * 
         * 이 메서드는 매 프레임 호출되어, 엔티티 상태나 애니메이션 프레임 갱신 등 
         * 렌더링에 필요한 정보를 준비합니다. 이후 Render 메서드에서 이 정보에 기반해 
         * 실제 화면에 그래픽 표현.
         */
        void Update(ECS::Manager& manager, const float dt) override final;

        /**
         * @brief 실제 화면에 그래픽을 그리는 Render 메서드
         * 
         * @param manager ECS::Manager 인스턴스
         * @param window SFML RenderWindow 인스턴스
         * 
         * 이 메서드는 준비된 엔티티 그래픽 정보를 바탕으로 스프라이트나 셰이프 등을 
         * 실제 화면에 그려줍니다. 엔티티별 위치, 스프라이트 텍스처, 애니메이션 프레임 등을 
         * 참조하여 정확한 위치와 모습으로 표현 가능.
         */
        void Render(ECS::Manager& manager, sf::RenderWindow& window);
    };
}
