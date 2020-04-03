#include "pch.h"
#include "EqManager.h"

#include "../COMPONENTS/Equipment.h"



void EqManager::init()
{
	update_components();
}


void EqManager::update_components()
{
	components.insert(componentManager->get_ComponentType<Equipment>());
	components.insert(componentManager->get_ComponentType<Inventory>());
}




void EqManager::update(Entity entity)
{
	currentEntity = entity;
	equipment = componentManager->get_component<Equipment>(currentEntity);
	inventory = componentManager->get_component<Inventory>(currentEntity);
	
	BodyPart equipTo;
	Entity item;

	std::vector<Event>& events = eventManager->get_eventsRef()[currentEntity];

	for (int i = 0; i < events.size(); i++) // this is used for AI to equip
	{
		if (events[i].get_type() == EventType::equipTo)
		{
			equipTo = static_cast<BodyPart>(events[i].get_value());
			item = events[i + 1].get_value();
			equip(equipTo, item);
		}
	}






}


void EqManager::equip(BodyPart bodyPart, Entity item)
{

	if (equipment.eq[bodyPart] != nullptr)
		unequip(bodyPart);

	LOG_NEW;
	equipment.eq[bodyPart] = new Entity (item);
}


void EqManager::unequip(BodyPart bodyPart)
{
	Entity unequip = *equipment.eq[bodyPart];
	delete equipment.eq[bodyPart];

	equipment.eq[bodyPart] = nullptr;

	inventory.inv.push_back(unequip);
}