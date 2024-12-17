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

/**
 * @file
 * @brief 이벤트 디스패처 헤더
 * 
 * 이벤트 등록, 통제하는 기능 수행.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include <functional>

#include "Event.hpp"

namespace MIR
{
    /**
     * @brief 이벤트를 처리하기 위한 Dispatcher 클래스
     * 
     * Dispatcher는 특정 이벤트 타입(EventType)에 대해 다수의 핸들러(리스너)를 등록하고,
     * 이벤트 발생 시 해당 타입에 연관된 모든 핸들러를 호출하는 역할 수행.
     */
    class Dispatcher
    {
        /**
         * @brief 이벤트 핸들러 타입 정의
         * 
         * 이벤트 오브젝트(shared_ptr<Event>)를 인자로 받아 처리하는 함수 객체 타입.
         */
        using Handler = std::function<void(const std::shared_ptr<Event>&)>;

    public:
        /**
         * @brief Dispatcher 기본 생성자
         * 
         * 초기 상태에서 등록된 리스너는 없음.
         */
        Dispatcher() = default;

        /**
         * @brief 특정 이벤트 타입에 대한 리스너(핸들러)를 등록하는 메서드
         * 
         * @param type 리스너를 등록할 이벤트 타입
         * @param handler 해당 이벤트 타입 발생 시 호출할 핸들러 함수
         * 
         * 동일 타입에 대해 여러 핸들러를 등록할 수 있으며, 이벤트 발생 시 순차적으로 호출.
         */
        void AddListener(EventType type, Handler handler);

        /**
         * @brief 이벤트를 디스패치(발생)하는 메서드
         * 
         * @param event 발생한 이벤트 객체
         * 
         * event의 타입에 해당하는 모든 핸들러를 호출하여 이벤트 처리.
         */
        void DispatchEvent(const std::shared_ptr<Event>& event);

    private:
        /**
         * @brief 이벤트 타입별로 등록된 핸들러를 관리하는 컨테이너
         * 
         * key: 이벤트 타입(EventType)
         * value: 해당 이벤트 타입에 대해 등록된 핸들러 함수들의 벡터
         * 
         * 이벤트 발생 시, 해당 타입에 매핑된 모든 핸들러를 호출하여 
         * 이벤트 처리 로직 수행.
         */
        std::unordered_map<EventType, std::vector<Handler>> listeners;
    };
}