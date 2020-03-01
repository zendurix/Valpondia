#pragma once

#include "Event.h"


class EventManager
{
	friend class ECS;

private:
	std::array<std::vector<Event>, MAX_ENTITIES> eventsPerEntity;


public:
	
	inline void send_event(Event event, Entity entity)
	{
		eventsPerEntity[entity].push_back(event);
	}


	inline void clear_events()
	{
		for (std::vector<Event>& vec : eventsPerEntity)
			vec.clear();
	}


	// getters
	inline std::array<std::vector<Event>, MAX_ENTITIES>& get_eventsRef() { return eventsPerEntity; }
};
