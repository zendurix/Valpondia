#pragma once

#include "ECS_config.h"
#include "ComponentManager.h"
#include "EventManager.h"
#include "Event.h"

class GAME;
class SystemManager;

// When making system function classes inherit from this one
class System
{
	friend class SystemManager;

protected:
	// systems have GAME ptr, so they can be called virtually, and none complex parameters are neeeded
	inline static GAME* gamePtr;

	// pointer to componentManager, so system can affect components
	inline static ComponoentManager* componentManager;

	// pointer to eventManager, so system can check for events
	inline static EventManager* eventManager;


	std::set<ComponentType> components;

	// set of entities, that are updated by this system
	std::set<Entity> entities;

public:
	inline static void set_gamePtr(GAME* game) { gamePtr = game; }
	inline static void set_componentManager(ComponoentManager* compManager) { componentManager = compManager; }
	inline static void set_eventManager(EventManager* eventmanager) { eventManager = eventmanager; }
	

	virtual void init() = 0;
	virtual void update(Entity entity) = 0;
	virtual void update_components() = 0;

	inline void update_all()
	{
		for (Entity entity : entities)
			update(entity);
	}
};



