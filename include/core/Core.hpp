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
 * @brief 모든 해더를 포함하는 헤더
 * 
 * 이 파일은 SFML(그래픽, 오디오), 표준 라이브러리(C++17 이상 가정), 
 * 그리고 엔티티, 컴포넌트, 시스템, 이벤트 관련 커스텀 헤더를 한 곳에서 포함.
 */

// SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// STD header
#include <cstdio>
#include <cstdint>
#include <cassert>

#include <memory>
#include <stdexcept>
#include <typeindex>

#include <unordered_map>
#include <vector>

#include <string>
#include <fstream>

// Custom header
#include "Entity.hpp"
#include "components/Components.hpp"
#include "systems/Systems.hpp"
#include "World.hpp"
#include "Storage.hpp"
#include "ServiceLocater.hpp"

#include "events/Events.hpp"
#include "events/Announcer.hpp"
#include "events/Dispatcher.hpp"
