// Created on Fri Nov 15 2024
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

#include <string>
#include <fstream>
#include <vector>

#include <json.hpp>

#include "ECSManager.hpp"
#include "components/Components.hpp"

/**
 * @file
 * @brief 게임 상태 저장 클래스 헤더
 * 
 * 엔티티 Query를 통해 직렬화가 필요한 데이터들을 JSON 파일에 세이브.
 */

namespace MIR
{
    /**
     * @brief ECS::Manager 상태(엔티티 및 컴포넌트) 정보를 파일로 저장/로드하는 클래스
     * 
     * Storage 클래스는 ECS::Manager 내부 상태를 JSON 형태로 파일에 기록하거나,
     * 기록된 JSON 데이터를 읽어 ECS::Manager를 복원하는 기능 제공.
     * 이를 통해 게임 상태나 월드 상태를 직렬화/역직렬화 할 수 있으며,
     * 세이브/로드 기능 구현이나 편집기 도구 제작에 유용하게 활용 가능.
     */
    class Storage
    {
    public:
        /**
         * @brief Storage 객체 생성자
         * 
         * @param path 저장/로드에 사용할 파일 경로
         * 
         * 지정한 경로에 ECS::Manager 상태를 저장하거나, 해당 경로에서 데이터 로드.
         */
        Storage(const std::string& path) : save_path(path)
        {

        }

        /**
         * @brief ECS::Manager 상태를 파일로 저장
         * 
         * 주어진 ECS::Manager 인스턴스에 포함된 엔티티 및 해당 컴포넌트 정보를 직렬화하여 JSON 형식으로 기록.
         * 이 메서드를 호출하기 전에 ECS::Manager가 올바르게 초기화되고, 
         * 필요한 엔티티와 컴포넌트를 가진 상태인지 확인해야함.
         * 
         * @param manager 상태를 저장할 ECS::Manager 인스턴스
         */
        void Save(ECS::Manager& manager);

        /**
         * @brief 파일에서 ECS::Manager 상태를 로드
         * 
         * save_path에 기록된 JSON 데이터를 읽어 ECS::Manager에 반영.
         * 이를 통해 이전에 저장했던 엔티티 구성, 컴포넌트의 복원 가능.
         * 
         * @param manager 상태를 로드할 ECS::Manager 인스턴스
         * @throws std::runtime_error 파일이 없거나 JSON 형식이 올바르지 않을 경우 예외 발생 가능
         */
        void Load(ECS::Manager& manager);

    private:
        /**
         * @brief ECS::Manager 상태를 저장/로드할 대상 파일 경로
         * 
         * Save/Load 시 이 경로를 사용하여 파일 접근 수행.
         */
        std::string save_path;
    };
}