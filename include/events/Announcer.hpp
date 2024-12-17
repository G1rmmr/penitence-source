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
 * @brief 이벤트 아나운서 헤더
 * 
 * 이벤트 전파 및 처리 기능 수행.
 */

#include <memory>
#include <queue>

#include "Events.hpp"
#include "Dispatcher.hpp"

namespace MIR
{
    /**
     * @brief 이벤트를 큐에 축적하고, Dispatcher를 통해 이를 처리하는 역할을 수행하는 클래스
     * 
     * Announcer는 이벤트를 즉시 처리하지 않고, PublishEvent를 통해 일단 큐에 푸시.
     * 이후 ProcessEvents를 호출하면 내부 큐의 이벤트들을 하나씩 꺼내 Dispatcher에 전달함.
     */
    class Announcer
    {
    public:
        /**
         * @brief 기본 생성자
         * 
         * 초기 상태에서 이벤트 큐는 비어 있으며, 향후 PublishEvent를 통해 이벤트 누적.
         */
        Announcer() = default;
        
        /**
         * @brief 이벤트를 큐에 추가하는 메서드
         * 
         * @param event 추가할 Event 객체의 shared_ptr
         * 
         * 게임 내에서 발생한 이벤트를 큐에 적재.
         * 쌓인 이벤트들은 추후 ProcessEvents 호출 시 처리.
         */
        void PublishEvent(const std::shared_ptr<Event>& event);

        /**
         * @brief 큐에 쌓인 이벤트를 처리하는 메서드
         * 
         * @param dispatcher 이벤트를 실제로 처리할 Dispatcher 참조
         * 
         * 큐에 적재된 이벤트들을 하나씩 꺼내 dispatcher로 전달하고, dispatcher는 해당 이벤트를 리스너들에게 알림.
         * 이를 통해 이벤트 처리를 일정한 시점에 일괄 처리 가능.
         */
        void ProcessEvents(Dispatcher& dispatcher);

    private:
        /**
         * @brief 대기 중인 이벤트들을 보관하는 큐
         * 
         * PublishEvent로 추가된 이벤트들이 여기 적재되며, 
         * ProcessEvents 호출 시 순차적으로 팝 되어 Dispatcher에 전달.
         */
        std::queue<std::shared_ptr<Event>> events;
    };
}
