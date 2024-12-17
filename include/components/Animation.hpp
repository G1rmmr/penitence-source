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
 * @brief 애니메이션 컴포넌트
 * 
 * 애니메이션 표현에 필요한 데이터 구조체.
 */

#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 애니메이션 데이터를 관리하는 컴포넌트 구조체
     *
     * 이 구조체는 프레임 정보를 담는 벡터와 애니메이션 재생 시간, 현재 프레임 인덱스, 
     * 루프 여부, 재생 상태 등을 관리. 
     * SFML의 IntRect를 이용하여 각 프레임이 차지하는 텍스처 영역을 정의하며, 
     * delay값으로 프레임 전환 간격 조정.
     */
    struct Animation final : public Component
    {
        /**
         * @brief 애니메이션을 구성하는 각 프레임의 영역 정보 목록
         *
         * 이 벡터는 각 애니메이션 프레임에 해당하는 SFML의 IntRect 저장.
         * IntRect는 텍스처 상에서 특정 부분을 지정하는 직사각형 영역.
         */
        std::vector<sf::IntRect> frames;

        /**
         * @brief 각 프레임 간 전환에 소요되는 시간(초 단위)
         *
         * 예를 들어 0.16f라면 약 0.16초마다 프레임이 다음으로 넘어감.
         */
        float delay;

        /**
         * @brief 현재까지 경과한 시간(초 단위)
         *
         * 프레임 전환을 위해 매 프레임 업데이트 시 누적되는 시간. 
         * delay를 초과하면 다음 프레임으로 전환되고, elapsed는 다시 0으로 초기화.
         */
        float elapsed;

        /**
         * @brief 현재 표시 중인 프레임의 인덱스
         *
         * frames 벡터를 기준으로 0부터 시작하는 인덱스를 가짐.
         * elapsed가 delay를 초과할 때마다 curr_frame을 증가시키며, 
         * is_looping이 true라면 마지막 프레임 후에 0으로 초기화.
         */
        std::size_t curr_frame;

        /**
         * @brief 애니메이션이 반복(loop) 재생되는지 여부
         *
         * true일 경우 마지막 프레임 이후 다시 첫 프레임으로 돌아가며 재생.
         * false일 경우 마지막 프레임에서 정지.
         */
        bool is_looping;

        /**
         * @brief 애니메이션이 현재 재생되고 있는지 여부
         *
         * true일 경우 elapsed 시간을 증가시키며 delay를 넘으면 프레임 전환이 일어남.
         * false라면 프레임 전환이 멈추며 현재 프레임 상태 유지.
         */
        bool is_playing;

        /**
         * @brief Animation 구조체의 기본 생성자
         *
         * 초기값으로 delay를 0.16초, elapsed를 0초, curr_frame을 0으로 설정.
         * 또한 기본적으로 애니메이션은 루프 재생(is_looping = true), 재생 중(is_playing = true) 상태.
         */
        Animation()
            : delay(0.16f), elapsed(0.f), curr_frame(0), is_looping(true), is_playing(true)
        {
        }
    };
}
