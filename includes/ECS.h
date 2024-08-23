#pragma once

#include <cstdio>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace GAlpha
{
	// Pre define for component class
	class Entity;
	
	// Super class of component
	class Component
	{
	public:
		Entity* entity;

		virtual void Init() {};
		virtual void Update() {};
		virtual void Draw() {};

		virtual ~Component() {}
	};

	// Type definitions
	constexpr std::size_t MAX_COMPONENTS = 32;
	
	using ComponentArr = std::array<Component*, MAX_COMPONENTS>;
	using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

	using ComponentID = std::size_t;

	// Type id will increases when component added.
	inline ComponentID GetComponentTypeID()
	{
		static ComponentID last_id = 0;
		return last_id++;
	}

	template <typename T>
	inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID type_id = GetComponentTypeID();
		return type_id;
	}

	// Simple Entity class
	class Entity
	{
	public:
		void Update()
		{
			for(auto& comp : components) comp->Update();
			for(auto& comp : components) comp->Draw();
		}

		void Draw() {}
		
		bool IsActivated() const {return activated;}
		void Destroy() {activated = false;}

		template <typename T>
		bool HasComponent() const
		{
			return components_bit_set[GetComponentTypeID<T>];
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
		T& GetComponent() const
		{
			auto ptr(components_arr[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

	private:
		std::vector<std::unique_ptr<Component>> components;
		ComponentArr components_arr;
		ComponentBitSet components_bit_set;
		bool activated = true;
	};

	class Manager
	{
	public:
		void Update()
		{
			for(auto& entity : *entities) entity->Update();
		}

		void Draw()
		{
			for(auto& entity : *entities) entity->Draw();
		}

		void Refresh()
		{
			entities->erase(std::remove_if(entities->begin(), entities->end(),
				[](const std::unique_ptr<Entity>& entity)
				{
					return !entity->IsActivated();
				}),
				entities->end());
		}

		Entity& AddEntity()
		{
			Entity* entity = new Entity();
			std::unique_ptr<Entity> enitiy_ptr{entity};

			entities->emplace_back(std::move(enitiy_ptr));
			return *entity;
		}

	private:
		std::vector<std::unique_ptr<Entity>>* entities
			= new std::vector<std::unique_ptr<Entity>>();
	};
}