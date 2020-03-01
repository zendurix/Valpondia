#pragma once

#include "ECS_config.h"
#include "ComponentArray.h"


// COMPONENT MANAGER - manages all ComponentArrays
class ComponoentManager
{
private:
	// map from component type string ptr to a component type
	std::unordered_map<const char*, ComponentType> componentTypes{};

	// map from string ptr to a component array
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

	// the component type to be assigned to next registered component - starting at 0
	ComponentType nextComponentType = 0;


	// function to get statically casted pointer to the ComponentArray of type T
	template <typename T>
	std::shared_ptr<ComponentArray<T>> get_component_array()
	{
		const char* typeName = typeid(T).name();

		assert(componentTypes.find(typeName) != componentTypes.end() && 
			"ECS ERROR [ComponentManager]: Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
	}


public:

	template <typename T>
	void register_component()
	{
		const char* typeName = typeid(T).name();

		assert(componentTypes.find(typeName) == componentTypes.end() && 
			"ECS ERROR [ComponentManager]: Registering component more than once.");

		// add this component type to component type map
		componentTypes.insert({ typeName, nextComponentType });

		// create ComponentArray pointer and addd it to the componentArrays map
		componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		// increment next component value, so the next comp registered will have different type
		nextComponentType++;
	}


	template <typename T>
	ComponentType get_ComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(componentTypes.find(typeName) != componentTypes.end() && 
			"ECS ERROR [ComponentManager]: Component not registered before use.");

		// return this component type - used for creating signatures
		return componentTypes[typeName];
	}


	template <typename T>
	void add_component(Entity entity, T component)
	{
		// add component to the array for an entity
		get_component_array<T>()->insert_data(entity, component);
	}


	template <typename T>
	void remove_component(Entity entity)
	{
		// remove the component of type T for an entity
		get_component_array<T>()->remove_data(entity);
	}


	template <typename T>
	T& get_component(Entity entity)
	{
		// get a reference fo the component for an entity from array
		return get_component_array<T>()->get_data(entity);
	}


	inline void entity_destroyed(Entity entity)
	{
		// tell each component array that an entity has been destroyed
		// if it has a component for that entity it will remove it

		for (auto const& pair : componentArrays)
		{
			auto const& component = pair.second;
			component->entity_destroyed(entity);
		}
	}
	   	  

	template<typename T>
	bool entity_have_this_component(Entity entity)
	{
		const char* typeName = typeid(T).name();
		return componentArrays[typeName]->entity_have_this_component(entity);
	}

};