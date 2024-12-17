// Created on Fri Nov 08 2024
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

#include <unordered_map>
#include <vector>
#include <bitset>
#include <memory>
#include <concepts>
#include <queue>

#include "Entity.hpp"
#include "components/Component.hpp"
#include "components/ComponentPool.hpp"

/**
 * @file
 * @brief ECS 매니저의 중추 설계 헤더
 * 
 * 엔티티를 등록하고, 컴포넌트를 등록하는 시스템이 정의됨.
 */

namespace MIR
{
    namespace ECS
    {
        /**
         * @brief 엔티티의 컴포넌트 보유 상태를 나타내는 비트 마스크 타입
         * 
         * MAX_COMPONENTS 크기의 비트셋을 통해 엔티티가 어떤 컴포넌트를 가지고 있는지 알 수 있음.
         * 각 비트는 특정 컴포넌트 유형을 나타내며, 비트가 1이면 해당 컴포넌트를 보유한 것을 의미.
         */
        using Mask = std::bitset<MAX_COMPONENTS>;

        /**
         * @brief 엔티티가 보유한 컴포넌트들을 관리하는 컨테이너 타입
         * 
         * key: Component::Tag(컴포넌트 식별용),
         * value: 커스텀 deleter가 적용된 컴포넌트 unique_ptr.
         * 이를 통해 엔티티의 컴포넌트의 할당 동적 관리.
         */
        using Data = std::unordered_map<Component::Tag,
            std::unique_ptr<Component, std::function<void(Component*)>>>;

        /**
         * @brief 컴포넌트 풀(Pool)을 가리키는 스마트 포인터 타입
         * 
         * 풀을 shared_ptr로 관리하여 다형성 유지 가능.
         */
        using Pool = std::shared_ptr<PoolBase>;

        /**
         * @brief ECS(Entity-Component-System) 아키텍처에서 엔티티와 컴포넌트를 관리하는 클래스
         * 
         * Manager는 엔티티 생성/소멸, 컴포넌트 추가/조회, 특정 컴포넌트 집합을 보유한 엔티티 조회 가능.
         * 내부적으로 마스크와 풀을 이용해 효율적인 컴포넌트 관리와 조회 성능을 제공.
         */
        class Manager
        {
        public:
            /**
             * @brief Manager 기본 생성자
             * 
             * 초기 상태에서는 엔티티나 컴포넌트가 없는 상태.
             */
            Manager() = default;

            /**
             * @brief 소멸자
             * 
             * Manager가 소멸될 때 모든 엔티티와 컴포넌트, 풀 등이 자동 해제.
             */
            ~Manager();

            /**
             * @brief 새로운 엔티티를 생성하고 ID를 반환
             * 
             * 새로운 엔티티 ID를 발급하고 마스크, 컴포넌트 맵을 초기화.
             * @return 생성된 엔티티의 ID
             */
            Entity::ID CreateEntity();

            /**
             * @brief 특정 엔티티를 소멸
             * 
             * 해당 엔티티가 가진 모든 컴포넌트 해제, 엔티티 ID를 재사용 가능하도록 처리.
             * @param id 소멸할 엔티티의 ID
             */
            void DestoryEntity(Entity::ID id);

            /**
             * @brief 엔티티에 새로운 컴포넌트를 추가하는 템플릿 메서드
             * 
             * 주어진 타입 T의 컴포넌트를 엔티티에 추가.
             * Args...는 컴포넌트 생성자에 전달되는 파라미터 팩이며, 
             * 풀을 통해 컴포넌트를 재할당하거나 새로 생성.
             * 
             * @tparam T 추가할 컴포넌트 타입
             * @tparam Args T 생성자에 전달할 파라미터 타입
             * @param id 컴포넌트를 추가할 엔티티의 ID
             * @param args 컴포넌트 생성자에 전달할 인자
             * @throws std::runtime_error 유효하지 않은 엔티티이거나, 이미 해당 컴포넌트를 보유한 경우
             */
            template <typename T, typename... Args>
            requires std::constructible_from<T, Args...>
            inline void AddComponent(Entity::ID id, Args&&... args)
            {
                if (masks.find(id) == masks.end())
                    throw std::runtime_error("Invalid Entity ID");

                Component::Tag tag = GetTag<T>();
                if (masks[id][tag])
                    throw std::runtime_error("Component already exists for this Entity");
                
                masks[id].set(tag);

                if(pools.find(tag) == pools.end())
                    pools[tag] = std::make_shared<ComponentPool<T>>();

                auto pool = std::static_pointer_cast<ComponentPool<T>>(pools[tag]);
                auto component = pool->Acquire(std::forward<Args>(args)...);
                components[id][tag] = std::move(component);
            }

            /**
             * @brief 엔티티로부터 특정 타입 T의 컴포넌트를 가져오는 메서드
             * 
             * 해당 엔티티가 T 타입의 컴포넌트를 가지고 있다면 포인터 반환, 없다면 nullptr 반환.
             * 
             * @tparam T 가져올 컴포넌트 타입
             * @param id 엔티티 ID
             * @return T* 컴포넌트 포인터, 없으면 nullptr
             */
            template <typename T>
            inline T* GetComponent(Entity::ID id)
            {
                Component::Tag tag = GetTag<T>();
                if(!masks[id][tag])
                    return nullptr;

                auto it = components.find(id);

                if(it != components.end() && it->second.find(tag) != it->second.end())
                    return static_cast<T*>(it->second[tag].get());

                return nullptr;
            }

            /**
             * @brief 엔티티가 특정 타입 T의 컴포넌트를 보유하는지 확인
             * 
             * 마스크를 통해 해당 컴포넌트 태그 비트가 설정되어 있는지 확인.
             * 
             * @tparam T 확인할 컴포넌트 타입
             * @param id 엔티티 ID
             * @return true 엔티티가 T 타입의 컴포넌트를 가지고 있음
             * @return false 없음
             */
            template <typename T>
            inline bool HasComponent(Entity::ID id)
            {
                Component::Tag tag = GetTag<T>();
                return masks[id][tag];
            }

            /**
             * @brief 특정 컴포넌트 집합을 모두 가진 엔티티 목록을 조회
             * 
             * 가변 템플릿 파라미터 팩(Components...)으로 전달된 모든 컴포넌트를 보유한 엔티티들 반환.
             * 마스크를 사용해 해당 컴포넌트 비트가 모두 설정된 엔티티를 필터링.
             * 
             * @tparam Components 요구되는 컴포넌트 타입들
             * @return std::vector<Entity::ID> 해당 컴포넌트를 전부 가진 엔티티 ID 목록
             */
            template <typename... Components>
            inline std::vector<Entity::ID> Query() const
            {
                std::vector<Entity::ID> result;

                for(const auto& [id, mask] : masks)
                    if((mask.test(GetTag<Components>()) && ...))
                        result.emplace_back(id);

                return result;
            }

        private:
            /// 엔티티별 컴포넌트 데이터를 관리하는 맵
            std::unordered_map<Entity::ID, Data> components;
            /// 엔티티별 컴포넌트 보유 마스크를 관리하는 맵
            std::unordered_map<Entity::ID, Mask> masks;
            /// 컴포넌트 태그별 풀(Pool)을 관리하는 맵
            std::unordered_map<Component::Tag, Pool> pools;

            /// 재사용 가능한 엔티티 ID를 관리하는 큐
            std::queue<Entity::ID> id_queue;
            
            /// 다음에 할당할 엔티티 ID
            inline static Entity::ID next_id = 0;
            /// 다음에 할당할 컴포넌트 태그
            inline static Component::Tag next_tag;

            /**
             * @brief 새로운 엔티티 ID를 발급
             * 
             * next_id를 증가시키며 새로운 ID 반환.
             * @return 새로운 엔티티 ID
             */
            inline Entity::ID GetID()
            {
                return next_id++;
            }
            
            /**
             * @brief 특정 컴포넌트 타입 T에 대한 태그를 얻는 정적 메서드
             * 
             * 최초 호출 시 next_tag를 할당받아 정적 변수에 저장하고, 
             * 이후 동일 타입 T에 대해서는 같은 태그 반환.
             * 
             * @tparam T 컴포넌트 타입
             * @return 해당 타입에 고유한 컴포넌트 태그
             */
            template <typename T>
            inline static Component::Tag GetTag()
            {
                static Component::Tag tag = next_tag++;
                return tag;
            }
        };
    }
}
