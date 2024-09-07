#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace GAlpha
{
	class Entity;
	class Manager;
	
	class Component
	{
	public:
		Entity* entity;

		virtual void Init() {};
		virtual void Update() {};
		virtual void Draw() {};

		virtual ~Component() {}
	};

	using ComponentID = std::size_t;

	inline ComponentID GetNewComponentTypeID()
	{
		static ComponentID last_id = 0u;
		return last_id++;
	}

	template <typename T>
	inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID type_id = GetNewComponentTypeID();
		return type_id;
	}

	constexpr std::size_t MAX_COMPONENTS = 32;
	
	using ComponentArr = std::array<Component*, MAX_COMPONENTS>;
	using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

	constexpr std::size_t MAX_GROUPS = 32;

	using GroupBitSet = std::bitset<MAX_GROUPS>;
	using Group = std::size_t;
	
	class Entity
	{
	public:
		Entity(Manager& manager) : manager(manager)
		{

		}

		void Update()
		{
			for(auto& comp : components) comp->Update();
		}

		void Draw()
		{
			for(auto& comp : components) comp->Draw();
		}
		
		inline bool IsActivated() const {return activated;}

		inline void Destroy() {activated = false;}

		template <typename T>
		inline bool HasComponent() const
		{
			return components_bit_set[GetComponentTypeID<T>()];
		}

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			T* component(new T(std::forward<TArgs>(args)...));
			component->entity = this;

			std::unique_ptr<Component> component_ptr{component};
			components.emplace_back(std::move(component_ptr));

			components_arr[GetComponentTypeID<T>()] = component;
			components_bit_set[GetComponentTypeID<T>()] = true;

			component->Init();

			return *component;
		}

		template<typename T>
		inline T& GetComponent() const
		{
			auto ptr(components_arr[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

		inline bool HasGroup(Group group) { return group_bit_set[group]; }

		void AddGroup(Group group);

		inline void DelGroup(Group group)
		{
			group_bit_set.reset(group);
		}

	private:
		std::vector<std::unique_ptr<Component>> components;

		ComponentArr components_arr;
		ComponentBitSet components_bit_set;
		GroupBitSet group_bit_set;

		Manager& manager;

		bool activated = true;
	};

	class Manager
	{
	public:
		void Update()
		{
			for(auto& entity : entities) entity->Update();
		}

		void Draw()
		{
			for(auto& entity : entities) entity->Draw();
		}

		void Refresh()
		{
			for(auto i(0u); i < MAX_GROUPS; ++i)
			{
				auto& vec(grouped_entities[i]);

				vec.erase(std::remove_if(
					std::begin(vec), std::end(vec),
					[i](Entity* entity)
					{
						return !entity->IsActivated() || !entity->HasGroup(i);
					}),
					std::end(vec));
			}

			entities.erase(std::remove_if(
				std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity>& entity)
				{
					return !entity->IsActivated();
				}),
				std::end(entities));
		}

		Entity& AddEntity()
		{
			Entity* ent = new Entity(*this);
			std::unique_ptr<Entity> entitiy_ptr{ent};

			entities.emplace_back(std::move(entitiy_ptr));
			return *ent;
		}

		inline void AddToGroup(Entity* entity, Group group)
		{
			grouped_entities[group].emplace_back(entity);
		}

		inline std::vector<Entity*>& GetGroup(Group group)
		{
			return grouped_entities[group];
		}

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		std::array<std::vector<Entity*>, MAX_GROUPS> grouped_entities;
	};
}