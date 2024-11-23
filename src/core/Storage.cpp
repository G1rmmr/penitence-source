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

#include "core/Storage.hpp"

using namespace MIR;
using namespace nlohmann;

void Storage::Save(ECSManager& manager)
{
    json state_json;
    json entities_json = json::array();

    std::vector<Entity::ID> entities = manager.Query<Position>();

    for(const auto& id : entities)
    {
        json entity_json;
        entity_json["id"] = id;

        Position* pos = manager.GetComponent<Position>(id);

        json j;
        j["x"] = pos->x;
        j["y"] = pos->y;

        entity_json["Position"] = j;
        entities_json.push_back(entity_json);
    }

    state_json["entities"] = entities_json;

    std::ofstream output(save_path);

    if (!output.is_open())
    {
        fprintf(stderr, "Failed to open file for saving game state.");
        return;
    }

    output << state_json.dump(4);
    output.close();
}

void Storage::Load(ECSManager& manager)
{
    std::ifstream input(save_path);
    assert(input.is_open() && "Failed to open file for saving game state.");

    json state_json;
    input >> state_json;
    input.close();

    for(const auto& entity_json : state_json["entities"])
    {
        Entity::ID id(entity_json["id"].get<Entity::ID>());

        if(entity_json.contains("Position"))
        {
            json j = entity_json["Position"];
            Position pos(j.at("x").get<float>(), j.at("y").get<float>());
            manager.AddComponent<Position>(id, std::move(pos));
        }
    }
}