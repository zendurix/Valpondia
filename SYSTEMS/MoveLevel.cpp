#include "pch.h"
#include "MoveLevel.h"

#include "../COMPONENTS/Position.h"
#include "../GAME.h"
#include "../Level.h"
#include "../Place.h"


void MoveLevel::init()
{
	update_components();
}

void MoveLevel::update(Entity entity)
{
	Event moveEvent = NULL_EVENT;
	for (Event& event : eventManager->get_eventsRef()[entity])
	{
		if (event.get_type() == EventType::moveLevel)
			moveEvent = event;
	}

	if (moveEvent != NULL_EVENT)
	{
		Position& pos = componentManager->get_component<Position>(entity);
		Connector connector = (*System::gamePtr->get_levels())[pos.levelID]->get_fieldRef()[pos.y][pos.x]->get_connector();
		(*System::gamePtr->get_levels())[pos.levelID]->get_fieldRef()[pos.y][pos.x]->leave_here();

		int levelDestination = moveEvent.get_value();
		pos.levelID = levelDestination;
		pos.y = connector.destinationY;
		pos.x = connector.destinationX;

		(*System::gamePtr->get_levels())[pos.levelID]->get_fieldRef()[pos.y][pos.x]->go_here(entity);
	}
}


void MoveLevel::update_components()
{
	components.insert(componentManager->get_ComponentType<Position>());
	components.insert(componentManager->get_ComponentType<Player>());  // for now only player can move through levels
}