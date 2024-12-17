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
 * @brief 시스템을 관리하는 클래스 헤더
 * 
 * 여러 시스템들을 한번에 관리하는 클래스
 */

#include <memory>
#include <vector>

#include "ECSManager.hpp"
#include "components/Components.hpp"
#include "systems/Systems.hpp"

namespace MIR
{
    /**
     * @brief ECS 아키텍처에서 시스템들을 관리하고, 게임 월드 상태를 업데이트/렌더링하는 클래스
     *
     * World 클래스는 ECSManager(엔티티와 컴포넌트 관리)와 여러 시스템(System)들을 연계.
     * Update 메서드를 통해 물리, AI, 애니메이션 등 다양한 시스템 로직을 실행하고,
     * Render 메서드를 통해 그래픽 출력과 관련된 시스템 호출.
     * 또한 AddSystem 템플릿 메서드를 통해 런타임에 다양한 시스템을 동적으로 추가.
     */
    class World
    {
    public:
        /**
         * @brief 기본 생성자
         * 
         * 초기 상태에서는 어떤 시스템도 추가되지 않은 빈 상태.
         */
        World() = default;
        
        /**
         * @brief 매 프레임마다 호출되어 게임 상태를 갱신하는 메서드
         * 
         * @param manager 엔티티와 컴포넌트를 관리하는 ECS::Manager
         * @param dt 델타 타임(초 단위), 현재 프레임에서 지난 프레임까지의 시간 간격
         * 
         * 이 메서드는 등록된 모든 시스템의 Update 로직을 호출하여 엔티티 상태를 변화시키거나,
         * 물리 연산 및 AI 판단 등을 수행.
         */
        void Update(ECS::Manager& manager, const float dt);

        /**
         * @brief 매 프레임 렌더링 단계에서 호출되어 그래픽을 그리는 메서드
         * 
         * @param manager 엔티티와 컴포넌트를 관리하는 ECS::Manager
         * @param window SFML의 렌더 윈도우
         * 
         * 이 메서드는 등록된 모든 시스템 중 렌더링 관련 로직을 수행하는 시스템을 호출하여
         * 화면에 엔티티 그래픽, UI 요소 등을 그림.
         */
        void Render(ECS::Manager& manager, sf::RenderWindow& window);
        
        /**
         * @brief 새로운 시스템을 동적으로 추가하는 템플릿 메서드
         * 
         * @tparam T 추가할 시스템 클래스 타입 (System 인터페이스를 상속해야 함)
         * 
         * 런타임에 시스템 인스턴스를 생성하고 systems 벡터에 보관.
         * 이후 Update, Render 호출 시 해당 시스템도 함께 처리.
         */
        template<typename T>
        inline void AddSystem()
        {
            std::unique_ptr<T> system = std::make_unique<T>();
            systems.emplace_back(std::move(system));
        }

    private:
        /**
         * @brief 등록된 시스템을 관리하는 벡터
         * 
         * Update, Render 메서드 호출 시 이 벡터 내 시스템들을 순회하며 
         * 각 시스템의 로직을 실행.
         */
        std::vector<std::unique_ptr<System>> systems;

        /**
         * @brief 특정 타입의 시스템을 얻는 유틸리티 템플릿 메서드
         * 
         * @tparam T 찾을 시스템 타입
         * @return T* 해당 타입의 시스템 포인터 (없으면 nullptr)
         * 
         * systems 벡터를 순회하며 dynamic_cast를 통해 T 타입 시스템을 검색.
         * 특정 시스템 인스턴스가 필요한 로직에서 활용 가능.
         */
        template<typename T>
        inline T* GetSystem()
        {
            for(const auto& sys : systems)
            {
                T* target = dynamic_cast<T*>(sys.get());
                if (target)
                    return target;
            }
            return nullptr;
        }
    };
}
