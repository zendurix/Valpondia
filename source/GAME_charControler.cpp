#include "pch.h"
#include "GAME_charControler.h"



GAME_charControler::GAME_charControler(GAME* game)
{
	g = game;
}

GAME_charControler::~GAME_charControler()
{
}


void GAME_charControler::move_level_down(Character* ch)
{
	bool break_ = false;
	if (!ch->get_isAI())
	{
		if (g->levelActiveId + 1 > Level::levelCount)
		{
			int lv = random(0, 1);
			enum lvType levelType;

			if (lv == 0)
			{
				levelType = cave;
			}
			else
			{
				levelType = dungeon;
			}
			g->make_new_level(levelType);
		}
		else
		{
			g->levelActive = g->levels[g->levelActiveId + 1];
		}
		g->levelActiveId = g->levelActive->depth;
		ch->set_onLevelID(ch->get_onLevelID() + 1);
	}
	else // isAI
	{
		if (ch->get_onLevelID() == Level::levelCount)
			break_ = true;	// AI moving down can't create new levels
		else
			ch->set_onLevelID(ch->get_onLevelID() + 1);
	}

	int levelChange = ch->get_onLevelID();

	if (!break_)
	{
		ch->set_fieldArr(&g->levels[levelChange]->field);
		ch->set_staysOn(g->levels[levelChange]->stairsUp);
		ch->set_x(g->levels[levelChange]->stairsUp->get_x());
		ch->set_y(g->levels[levelChange]->stairsUp->get_y());

		g->levels[levelChange]->field[ch->get_y()][ch->get_x()]->go_here(ch);


		g->levels[levelChange]->set_true_all_changedPrint(); ///////////////
	}

}

void GAME_charControler::move_level_up(Character* ch)
{
	if (!ch->get_isAI())
	{
		g->levelActive = g->levels[g->levelActiveId - 1];
		g->levelActiveId = g->levelActive->depth;
	}
	ch->set_onLevelID(ch->get_onLevelID() - 1);
	int levelChange = ch->get_onLevelID();

	ch->set_fieldArr(&g->levels[levelChange]->field);
	ch->set_staysOn(g->levels[levelChange]->stairsDown);
	ch->set_x(g->levels[levelChange]->stairsDown->get_x());
	ch->set_y(g->levels[levelChange]->stairsDown->get_y());
	g->levels[levelChange]->field[ch->get_y()][ch->get_x()]->go_here(ch);
	g->levels[levelChange]->set_true_all_changedPrint(); //////////////////////
}

char GAME_charControler::player_turn()
{
	char action = user_input_key();

	if (action >= '0' && action <= '9')
	{
		g->player->move(action);
	}
	else if (action == '+')
	{
		if (g->player->get_staysOn()->get_stairsUp())
			move_level_up(g->player);
	}
	else if (action == '-')
	{
		if (g->player->get_staysOn()->get_stairsDown())
			move_level_down(g->player);
	}
	else if (action == 'U')
	{
		g->Printer->print_field();
		wait_for_input(space);
	}
	else if (action == 'p')
	{
		pick_up_item(g->player);
	}
	else if (action == 'i')
	{
		player_inventory_control();
	}

	sleep_for_milliseconds(50);
	return action;
}

void GAME_charControler::place_character_randomly(Character* ch)
{
	std::shared_ptr<Place> place_here = g->levelActive->field[0][0];
	do
	{
		place_here = g->levelActive->field[random(1, MYHEIGHT - 2)][random(1, MYLENGTH - 2)];

	} while ((g->levelActive->levelType == cave && place_here->get_isObstacle()) ||
		(g->levelActive->levelType == dungeon && !place_here->get_isInRoom()));

	place_here->go_here(ch);
	ch->set_x(place_here->get_x());
	ch->set_y(place_here->get_y());
	ch->set_staysOn(place_here);
}



void GAME_charControler::pick_up_item(Character* ch)
{
	g->reset_visibility(*g->player); // to avoid flickering tiles
	g->Printer->print_field_UPDATE();

	std::vector<std::shared_ptr<Item>> *items = ch->get_staysOn()->get_itemsHere_ptr();
	if (items->size() == 0)
	{
		LOG("NO ITEMS HERE"); // add in game message
	}
	else
	{
		std::vector<std::shared_ptr<Item>> picked = UI::pick_items_window(items);
		for (std::shared_ptr<Item> item : picked)
		{
			ch->pick_item(item);
			ch->get_staysOn()->pick_up(item);
		}
	}
}




void GAME_charControler::player_inventory_control()
{
	UI::player_inventory_window();
}