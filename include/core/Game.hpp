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

#include "core/Core.hpp"
#include "Protagonist.hpp"

// TO-DO : SFML 라이브러리를 추상화하여 오로지 MIR 라이브러리만을 사용할 것.

/**
 * @file
 * @brief Game 세팅, 실제 게임이 구현되는 워크 스페이스
 * 
 * 게임 로직 관리 가능.
 */

namespace MIR
{
    /**
     * @brief 게임의 전반적인 실행을 관리하는 클래스.
     * 
     * Game 클래스는 초기화, 이벤트 처리, 게임 상태 업데이트, 렌더링, 종료 등을 포함한 게임 루프 주요 작업 수행.
     */
    class Game
    {
    public:
        /**
         * @brief Game 클래스의 생성자.
         * 
         * 게임 객체 초기화.
         */
        Game();

        /**
         * @brief Game 클래스의 소멸자.
         * 
         * 게임 사용한 자원 정리.
         */
        ~Game();

        /**
         * @brief 게임 초기화 함수.
         * 
         * 게임 창, 리소스, ECS 시스템 등을 초기화.
         */
        void Init();

        /**
         * @brief 이벤트 처리 함수.
         * 
         * 사용자 입력 및 기타 이벤트 처리.
         */
        void HandleEvent();

        /**
         * @brief 게임 상태 업데이트 함수.
         * 
         * 게임 로직 및 ECS 시스템 상태 업데이트.
         */
        void Update();

        /**
         * @brief 게임 루프 실행 함수.
         * 
         * 메인 게임 루프 실행.
         */
        void Run();

        /**
         * @brief 화면 렌더링 함수.
         * 
         * 화면에 게임의 현재 상태 렌더링.
         */
        void Render();

        /**
         * @brief 게임 종료 함수.
         * 
         * 게임 종료 시 필요한 작업 처리.
         */
        void Shutdown();

        /**
         * @brief 게임 창이 열려 있는지 확인.
         * 
         * @return true 게임 창이 열려 있음.
         * @return false 게임 창이 닫혀 있음.
         */
        inline bool IsRunning() const
        {
            return window->isOpen();
        }

    private:
        const std::string WINDOW_TITLE = "The Penitence"; /**< 게임 창 제목. */
        const std::string SAVE_PATH = "../savedata/save.json"; /**< 저장 데이터 경로. */

        const uint16_t WINDOW_WIDTH = 800; /**< 게임 창 너비. */
        const uint16_t WINDOW_HEIGHT = 600; /**< 게임 창 높이. */

        std::unique_ptr<sf::RenderWindow> window; /**< SFML 렌더링 창. */
        std::unique_ptr<sf::Event> event; /**< 사용자 입력 이벤트 처리하는 객체. */
        std::unique_ptr<sf::Music> music; /**< 배경 음악 재생하는 객체. */

        std::unique_ptr<World> world; /**< 게임 월드 데이터 관리 객체. */
        std::unique_ptr<ECS::Manager> manager; /**< ECS 시스템 관리자 객체. */
        std::unique_ptr<Storage> storage; /**< 저장 데이터 관리 객체. */
    };
}