#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>

namespace GAlpha
{
    class Entity
    {
    public:
        Entity(int id) : id(id) {}

        template<typename T>
        void AddComponent(std::shared_ptr<T> component)
        {
            auto index = std::type_index(typeid(T));
            components[index] = component;
        }

        template<typename T>
        std::shared_ptr<T> GetComponent()
        {
            auto component = components[std::type_index(typeid(T))];
            return std::static_pointer_cast<T>(component);
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<void> > components;
        int id;

    };
}