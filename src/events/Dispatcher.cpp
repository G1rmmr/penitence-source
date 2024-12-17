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

#include "events/Dispatcher.hpp"

using namespace MIR;

void Dispatcher::AddListener(EventType type, Handler handler)
{
    listeners[type].emplace_back(handler);
}

void Dispatcher::DispatchEvent(const std::shared_ptr<Event>& event)
{
    auto it = listeners.find(event->type);

    if(it != listeners.end())
        for(auto& handler : it->second)
            handler(event);
}
