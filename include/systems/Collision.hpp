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
 * @brief 충돌 시스템 헤더
 */

#include "System.hpp"
#include "components/Collider.hpp"
#include "components/Position.hpp"

namespace MIR
{
    /**
     * @brief 엔티티 간 충돌을 감지하고 처리하는 시스템 클래스
     * 
     * Collision 시스템은 ECS::Manager를 통해 엔티티들의 Collider, Position 컴포넌트를 조회하고,
     * 프레임별로 충돌 감지 로직 실행.
     */
    class Collision final : public System
    {
    public:
        /**
         * @brief 충돌 검사를 수행하는 Update 메서드
         * 
         * @param manager 엔티티 및 컴포넌트를 관리하는 ECS::Manager
         * @param dt 델타 타임(초 단위)
         * 
         * 이 메서드는 매 프레임 호출되어,
         * 현재 월드에 존재하는 모든 엔티티 쌍에 대해 충돌 여부 판정 가능.
         */
        void Update(ECS::Manager& manager, const float dt) override final;

    private:
        /**
         * @brief 두 엔티티의 위치 및 콜라이더 정보로 충돌 여부를 판정하는 헬퍼 함수
         * 
         * @param left_pos 첫 번째 엔티티의 위치
         * @param right_pos 두 번째 엔티티의 위치
         * @param left_box 첫 번째 엔티티의 콜라이더
         * @param right_box 두 번째 엔티티의 콜라이더
         * @return true 충돌 발생
         * @return false 충돌 없음
         * 
         * 단순 AABB(축 정렬 바운딩 박스) 충돌 검사 방식을 사용.
         * 상자 간 좌표 범위가 겹치는지 확인하여 충돌 여부 판단.
         */
        inline bool IsColliding(
            const Position* left_pos,
            const Position* right_pos,
            const Collider* left_box,
            const Collider* right_box) const
        {
            return (left_pos->x < right_pos->x + right_box->width
                && left_pos->x + left_box->width > right_pos->x
                && left_pos->y < right_pos->y + right_box->height
                && left_pos->y + left_box->height > right_pos->y);
        }
    };
}
