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

#include "Event.hpp"
#include "Keyboard.hpp"
#include "PlayerCollided.hpp"

/**
 * @file
 * @brief 다양한 이벤트 클래스를 한 데 모아 포함하는 헤더 파일
 *
 * 이 파일은 기본 Event 클래스( Event.hpp )를 비롯하여,
 * 키보드 입력 이벤트( Keyboard.hpp ), 플레이어 충돌 이벤트( PlayerCollided.hpp ) 등
 * 게임 내 발생 가능한 다양한 이벤트를 한 번에 참조할 수 있도록 합니다.
 * 
 * 이를 통해 다른 소스 파일에서 이 파일을 포함하면 
 * 다양한 이벤트 타입을 쉽게 접근하고 처리할 수 있습니다.
 */
