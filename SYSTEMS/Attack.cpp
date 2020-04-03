#include "pch.h"
#include "Attack.h"

#include "../COMPONENTS/Actor.h"
#include"../general_purpose_func.h"


void Attack::init()
{
	update_components();
}



void Attack::update(Entity entity)
{
	Entity target = MAX_ENTITIES;
	for (Event& event : eventManager->get_eventsRef()[entity])
		if (event.get_type() == EventType::doAttack)
			target = event.get_value();

	if (target != MAX_ENTITIES)
	{
		std::vector<Event>& events = eventManager->get_eventsRef()[entity];
		for (int i = 0; i < events.size(); i++)
			if (events[i].get_type() == EventType::doPhysicDmg)
			{
				eventManager->send_event(Event{ EventType::takePhysicDmg, events[i].get_value() }, target);
				eventManager->send_event(Event{ EventType::takePenetration, events[i+1].get_value() }, target);
			}
	}


}



void Attack::update_components()
{
	components.insert(componentManager->get_ComponentType<Actor>());

}