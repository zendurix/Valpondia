#pragma once

#include "ECS_config.h"

class ECS;

// ENTITY MANAGER - distributes unique IDs to new Entities, and keep record which IDs are in use
class EntityManager
{
	friend class ECS;
private:

	std::queue<Entity> aviableEntitiesIDs;
	std::array<Signature, MAX_ENTITIES> signatures;
	uint32_t livingEntityCount{};


public:

	inline EntityManager()
	{
		// initialize queue with all possible IDs
		for (Entity i = 0; i < MAX_ENTITIES; i++)
			aviableEntitiesIDs.push(i);
	}


	inline Entity create_entity()
	{
		assert(livingEntityCount < MAX_ENTITIES && "ECS ERROR [EntityManager]: Too many Entities to create new one."); 

		// take out id from front of the queue
		Entity newEntityID = aviableEntitiesIDs.front();
		aviableEntitiesIDs.pop();
		livingEntityCount++;

		return newEntityID;
	}


	inline void destroy_entity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "ECS ERROR [EntityManager]: Entity to be destroyd is out of range.");

		// reset entity signature (set all to false - 0 )
		signatures[entity].reset();

		// put destroyd entity ID on back of the queue, so it can be used to create new one
		aviableEntitiesIDs.push(entity);
		livingEntityCount--;
	}


	inline void set_signature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "ECS ERROR [EntityManager]: Entity to set signature is out of range.");

		// put entity signature into the array
		signatures[entity] = signature;
	}


	inline Signature get_signature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "ECS ERROR [EntityManager]: Entity to get signature is out of range.");

		// get the entity's signature form the array
		return signatures[entity];
	}


};


