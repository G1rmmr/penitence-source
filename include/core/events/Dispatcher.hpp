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

#include <unordered_map>
#include <vector>
#include <functional>

#include "Event.hpp"

namespace G2D
{
    class Dispatcher
    {
        using Handler = std::function<void(const std::shared_ptr<Event>&)>;

    public:
        Dispatcher() = default;

        void AddListener(EventType type, Handler handler);
        void DispatchEvent(const std::shared_ptr<Event>& event);

    private:
        std::unordered_map<EventType, std::vector<Handler>> listeners;
    };
}