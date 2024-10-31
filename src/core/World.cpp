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

#include "core/World.hpp"

using namespace G2D;

const std::string SAVE_FILE = "../savedata/save.json";

void World::AddEntity(const Entity& entity)
{
    if(last_id != entity.GetID())
    {
        entities[last_id] = entity;
        ++last_id;
    }
}

void World::RemoveEntity(Entity& entity)
{
    entities.erase(entity.GetID());
}

void World::Update(const float dt)
{
    for(auto& [_, sys] : systems)
    {
        for(auto& [_, entity] : entities)
            sys->Update(entity, dt);
    }
}

void World::Render()
{
    for(auto& [_, sys] : systems)
    {
        for(auto& [_, entity] : entities)
            sys->Render(entity);
    }
}

using namespace nlohmann;

void World::Save()
{
    json state_json;
    json entities_json = json::array();

    for(const auto& [_, entity] : entities)
    {
        json entity_json;
        entity_json["id"] = entity.GetID();

        if(entity.HasComponent<Transform>())
        {
            Transform& transf = entity.GetComponent<Transform>();

            json j;
            j["pos_x"] = transf.pos.x;
            j["pos_y"] = transf.pos.y;
            j["vel_x"] = transf.vel.x;
            j["vel_y"] = transf.vel.y;

            entity_json["Transform"] = j;
        }
        entities_json.push_back(entity_json);
    }

    state_json["entities"] = entities_json;

    std::ofstream output(SAVE_FILE);

    if (!output.is_open())
    {
        fprintf(stderr, "Failed to open file for saving game state.");
        return;
    }

    output << state_json.dump(4);
    output.close();
}

void World::Load(Entity& protagonist)
{
    std::ifstream input(SAVE_FILE);
    assert(input.is_open() && "Failed to open file for saving game state.");

    json state_json;
    input >> state_json;
    input.close();

    for (const auto& entity_json : state_json["entities"])
    {
        Entity entity(entity_json["id"].get<Entity::ID>());
        printf("%d\n", entity.GetID());

        if (entity_json.contains("Transform"))
        {
            entity.AddComponent<Transform>();
            json j = entity_json["Transform"];

            Transform& transf = entity.GetComponent<Transform>();
            transf.pos.x = j.at("pos_x").get<float>();
            transf.pos.y = j.at("pos_y").get<float>();
            transf.vel.x = j.at("vel_x").get<float>();
            transf.vel.y = j.at("vel_y").get<float>();

            protagonist = entity;
        }
    }
}