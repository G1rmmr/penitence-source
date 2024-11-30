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

namespace MIR
{
    class ServiceLocator
    {
    public:
        static ServiceLocator& Instance()
        {
            static ServiceLocator instance;
            return instance;
        }

        template<typename ServiceType>
        inline void RegisterService(std::shared_ptr<ServiceType> service)
        {
            services[typeid(ServiceType)] = service;
        }

        template<typename ServiceType>
        inline std::shared_ptr<ServiceType> GetService()
        {
            auto it = services.find(typeid(ServiceType));

            if (it != services.end())
                return std::static_pointer_cast<ServiceType>(it->second);
            else
                throw std::runtime_error("Service not found!");
        }

        template<typename ServiceType>
        inline bool HasService() const
        {
            return services.find(typeid(ServiceType)) != services.end();
        }

    private:
        ServiceLocator() = default;
        ~ServiceLocator() = default;

        ServiceLocator(const ServiceLocator&) = delete;
        ServiceLocator& operator=(const ServiceLocator&) = delete;

        std::unordered_map<std::type_index, std::shared_ptr<void>> services;
    };
}
