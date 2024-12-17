// Created on Wed Nov 27 2024
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

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

/**
 * @file
 * @brief Service Locater 클래스 헤더
 * 
 * 익히 알고 있는 중추 서비스 로케이터.
 */

namespace MIR
{
    /**
     * @brief 다양한 서비스(인터페이스 구현체)를 등록하고 조회하는 Service Locator 클래스
     * 
     * ServiceLocator는 싱글턴 패턴으로 생성,
     * 필요에 따라 여러 타입의 서비스를 동적으로 등록하고, 다른 곳에서 쉽게 조회할 수 있도록 함.
     *
     * 이 클래스를 통해 서비스 의존성을 간단히 해결할 수 있으나,
     * 의존성 역전 원리나 의존성 주입 방식에 비해 의존 관계가 명확히 드러나지 않을 수 있으므로 주의.
     */
    class ServiceLocator
    {
    public:
        /**
         * @brief ServiceLocator 인스턴스를 전역적으로 접근하기 위한 정적 메서드
         * 
         * 싱글턴 패턴을 사용하여 전역에 유일한 ServiceLocator 인스턴스 제공.
         * 
         * @return ServiceLocator& 전역적으로 접근 가능한 ServiceLocator 참조
         */
        static ServiceLocator& Instance()
        {
            static ServiceLocator instance;
            return instance;
        }

        /**
         * @brief 특정 타입의 서비스를 등록하는 템플릿 메서드
         * 
         * @tparam ServiceType 등록할 서비스 타입
         * @param service 공유 포인터 형태로 제공되는 서비스 구현체
         * 
         * typeid(ServiceType)를 키로 하는 맵에 service 저장.
         * 이후 다른 곳에서 GetService<ServiceType>()를 통해 서비스 조회 가능.
         */
        template<typename ServiceType>
        inline void RegisterService(std::shared_ptr<ServiceType> service)
        {
            services[typeid(ServiceType)] = service;
        }

        /**
         * @brief 특정 타입의 서비스를 조회하는 템플릿 메서드
         * 
         * @tparam ServiceType 조회할 서비스 타입
         * @return std::shared_ptr<ServiceType> 요청한 서비스에 대한 공유 포인터
         * @throws std::runtime_error 서비스가 등록되어 있지 않을 경우 예외 발생
         * 
         * 서비스 존재시 정적 캐스팅하여 반환, 없으면 예외 던짐.
         */
        template<typename ServiceType>
        inline std::shared_ptr<ServiceType> GetService()
        {
            auto it = services.find(typeid(ServiceType));

            if (it != services.end())
                return std::static_pointer_cast<ServiceType>(it->second);
            else
                throw std::runtime_error("Service not found!");
        }

        /**
         * @brief 특정 타입의 서비스 등록 여부를 확인하는 템플릿 메서드
         * 
         * @tparam ServiceType 확인할 서비스 타입
         * @return true 서비스가 등록되어 있음
         * @return false 서비스가 등록되어 있지 않음
         * 
         * services 맵을 조회하여 ServiceType 키가 존재하는지 확인.
         */
        template<typename ServiceType>
        inline bool HasService() const
        {
            return services.find(typeid(ServiceType)) != services.end();
        }

    private:
        /**
         * @brief 기본 생성자 (private)
         * 
         * 싱글턴 패턴을 위해 private로 숨기며, 외부에서 직접 인스턴스화 금지.
         */
        ServiceLocator() = default;

        /**
         * @brief 소멸자
         * 
         * 소멸 시 등록된 서비스는 shared_ptr를 통해 자동 관리.
         */
        ~ServiceLocator() = default;

        /**
         * @brief 복사 생성자 삭제
         * 
         * 싱글턴 패턴을 위해 복사 생성자 삭제.
         */
        ServiceLocator(const ServiceLocator&) = delete;

        /**
         * @brief 대입 연산자 삭제
         * 
         * 싱글턴 패턴을 위해 대입 연산자 삭제.
         */
        ServiceLocator& operator=(const ServiceLocator&) = delete;

        /**
         * @brief 서비스들을 관리하는 맵
         * 
         * key: std::type_index(서비스 타입 정보), 
         * value: void* 형태를 shared_ptr로 관리하는 포인터 (다형성 지원)
         */
        std::unordered_map<std::type_index, std::shared_ptr<void>> services;
    };
}