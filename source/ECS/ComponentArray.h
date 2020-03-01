#pragma once

#include "ECS_config.h"


// COMPONENT ARRAY - array of all in use components of one type
class IComponentArray                                                    // generic - ogolny
{ // interface is needed, so that ComponentManager (seen later) can tell a generic ComponentArray that Entity is destroyed
public:
	virtual void entity_destroyed(Entity entity) = 0;
	virtual bool entity_have_this_component(Entity entity) = 0; 
}; 


// ComponentArray is template, so that it can hold different Components
template <typename T>
class ComponentArray : public IComponentArray
{
private:
	// packed array of component of one type (T) set to max number of Entities, so each entity have spot for Component
	std::array<T, MAX_ENTITIES> componentArray;

	std::unordered_map<Entity, size_t> entityToIndexMap;
	std::unordered_map<size_t, Entity> indexToEntityMap;

	// size of valid Components in array
	size_t size;

public:
	inline void insert_data(Entity entity, T component)
	{
		assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && 
			"ECS ERROR [ComponentArray]: Component add to same entity more than once.");

		// put component at end of an array, and update the maps
		size_t new_index = size;
		entityToIndexMap[entity] = new_index;
		indexToEntityMap[new_index] = entity;
		componentArray[new_index] = component;
		size++;
	}


	inline void remove_data(Entity entity)
	{
		assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && 
			"ECS ERROR [ComponentArray]: Removing non existing component.");

		// copy element at the end into deleted element's place, to maintain array density
		size_t indexOfRemovedEntity = entityToIndexMap[entity];
		size_t indexOfLastElement = size - 1;
		componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

		// update maps to point to moved spot
		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);
		size--;
	}


	inline T& get_data(Entity entity)
	{
		assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && 
			"ECS ERROR [ComponentArray]: getting data of non existing component.");

		// return a refernece to the entity's component
		return componentArray[entityToIndexMap[entity]];
	}


	inline void entity_destroyed(Entity entity) override
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			// remove the entity's component, if it exists
			remove_data(entity);
		}
	}


	inline bool entity_have_this_component(Entity entity)
	{
		if (entityToIndexMap.find(entity) == entityToIndexMap.end())			return false;
		else			return true;
	}

};
