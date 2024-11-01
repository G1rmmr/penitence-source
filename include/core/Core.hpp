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