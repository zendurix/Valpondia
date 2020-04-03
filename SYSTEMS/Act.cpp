#include "pch.h"
#include "Act.h"

#include "../COMPONENTS/Actor.h"
#include "../COMPONENTS/Player.h"
#include "../COMPONENTS/Position.h"
#include "../GAME.h"
#include "../Level.h"
#include "../Place.h"
#include "../Input.h"
#include "../PathFinding.h"
#include "../general_purpose_func.h"


void Act::init()
{
	update_components();
}


void Act::update(Entity entity)
{
	if (componentManager->entity_have_this_component<Player>(entity))
		act_player(entity);
	else if (componentManager->entity_have_this_component<AI>(entity))
		act_AI(entity);
}


void Act::update_components()
{
	components.insert(componentManager->get_ComponentType<Actor>());
	components.insert(componentManager->get_ComponentType<Position>());
}




void Act::act_player(Entity player)
{
	char action = Input::user_input_key();
	bool finish = false;
	Position pos = componentManager->get_component<Position>(player);

	SharedPtr<Place> playerPlace = gamePtr->get_levelActive()->get_fieldRef()[pos.y][pos.x];

	Connector& connectorUnderPlayer = playerPlace->get_connector();


	if (connectorUnderPlayer != Place::NULLConnector)
	{
		if (action == connectorUnderPlayer.pushToGo)
		{
			finish = true;
			if (connectorUnderPlayer.destinationLevel == -10)
			{
				LOG("YOU WALK AWAY FROM YOUR DESTINY...");				
			}
			else
			{
				gamePtr->make_level(connectorUnderPlayer);
				eventManager->send_event(Event(EventType::moveLevel, connectorUnderPlayer.destinationLevel), player);
			}
		}
	}

	if (!finish && action >= '0' && action <= '9')
	{
		Event event(EventType::move, action - '0');   // subtract '0' from char to get numeric value
		eventManager->send_event(event, player);

		//Character* attackThis = g.player->move_and_attack(action);
		//if (attackThis != nullptr)
		//	attack(g.player, attackThis);
	}
	else if (!finish)
	{
		// to duplicate game state on both windows - to avoid background to "UI's" windows flickering
		//g.Printer.print_field();
	
		switch (action)
		{
				case '+':
				if (pos.levelID != 0 && pos.levelID != 1 && pos.levelID != 2)
				{
					SharedPtr<Place> stairsUp = gamePtr->get_levelActive()->get_stairsUp();
					if (stairsUp != nullptr)
					{
						char dir = PathFinding::best_dir(&gamePtr->get_levelActive()->get_fieldRef(), playerPlace, stairsUp);
						eventManager->send_event(Event{ EventType::move, dir - '0' }, player);
					}
				}
				break;
				case '-':
				if (pos.levelID != 0 && pos.levelID != 1)
				{
					SharedPtr<Place> stairsDown = gamePtr->get_levelActive()->get_stairsDown();
					if (stairsDown != nullptr)
					{
						char dir = PathFinding::best_dir(&gamePtr->get_levelActive()->get_fieldRef(), playerPlace, stairsDown);
						eventManager->send_event(Event{ EventType::move, dir - '0' }, player);
					}
				}
				break;
			



			//case 'U':
			//{
			//	gamePtr->Printer->print_field_all_visible();
			//	Input::wait_for_input(inputType::space);
			//	break;
			//}
			//case 'p':
			//{
			//	pick_up_item(g->player);
			//	break;
			//}
			//case 'i':
			//{
			//	player_inventory_control();
			//	break;
			//}
			//case 'e':
			//{
			//	player_equipment_control();
			//	break;
			//}
			default:
				break;
		}
	}

	//sleep_for_milliseconds(15);
}



void Act::act_AI(Entity aiEnt)
{
	AI ai = componentManager->get_component<AI>(aiEnt);


	switch (ai.behavior)
	{
	case Behavior::guarding:
		{
			switch (ai.attitude)
			{
				case Attitude::hostile:
				{


				}
				break;
			}

		}
		break;



	}





}





bool Act::sees_this_place(Entity entity, SharedPtr<Place> place)
{
	Position pos = componentManager->get_component<Position>(entity);

	SharedPtr<Place> entityPlace = gamePtr->get_place(pos);



}