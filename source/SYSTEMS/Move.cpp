#include "pch.h"
#include "Move.h"

#include "../COMPONENTS/Position.h"
#include "../COMPONENTS/Obstacle.h"
#include "../GAME.h"
#include "../Level.h"
#include "../Place.h"


void Move::init()
{
	update_components();
	//eventToTrigger = EventType::move;
}


void Move::update(Entity entity)
{
	Event moveEvent = NULL_EVENT;
	for (Event& event : eventManager->get_eventsRef()[entity])
	{
		if (event.get_type() == EventType::move)
			moveEvent = event;
	}

	if (moveEvent != NULL_EVENT)
	{
		Position& pos = componentManager->get_component<Position>(entity);
		Position prev = pos;

		System::gamePtr->get_levelActive()->get_fieldRef()[pos.y][pos.x]->leave_here();

		switch (moveEvent.get_value())
		{
		case 1: pos.x -= 1; pos.y += 1; break;
		case 2:				pos.y += 1; break;
		case 3: pos.x += 1; pos.y += 1; break;
		case 4: pos.x -= 1;				break;
		case 5:	/* wait turn */			break;
		case 6: pos.x += 1;				break;
		case 7: pos.x -= 1; pos.y -= 1; break;
		case 8:				pos.y -= 1; break;
		case 9: pos.x += 1; pos.y -= 1; break;
		}
		if (!border_cross(pos))
		{
			if (System::gamePtr->get_levelActive()->get_fieldRef()[pos.y][pos.x]->get_isObstacle())
				pos = prev;
		}
		else
			pos = prev;

		System::gamePtr->get_levelActive()->get_fieldRef()[pos.y][pos.x]->go_here(entity);
	}
}


void Move::update_components()
{
	components.insert(componentManager->get_ComponentType<Position>());
}



bool Move::border_cross(const Position& pos)
{
	if (pos.x == -1 || pos.x == MYLENGTH || pos.y == -1 || pos.y == MYHEIGHT)
		return true;
	return false;
}