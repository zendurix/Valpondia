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
	FieldOfView::set_fieldArr(&g->levelActive->field);
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
	FieldOfView::set_fieldArr(&g->levelActive->field);
}

char GAME_charControler::player_turn()
{
	char action = Input::user_input_key();

	if (action >= '0' && action <= '9')
	{
		g->player->move(action);
	}
	else
	{
		// to duplicate game state on both windows - to avoid background to "UI's" windows flickering
		g->Printer->print_field_UPDATE();

		switch (action)
		{
			case '+':
			{
				if (g->player->get_staysOn()->get_stairsUp())
					move_level_up(g->player);
				break;
			}
			case '-':
			{
				if (g->player->get_staysOn()->get_stairsDown())
					move_level_down(g->player);
				break;
			}
			case 'U':
			{
				g->Printer->print_field();
				Input::wait_for_input(inputType::space);
				break;
			}
			case 'p':
			{
				pick_up_item(g->player);
				break;
			}
			case 'i':
			{
				player_inventory_control();
				break;
			}
			case 'e':
			{
				player_equipment_control();
				break;
			}
			default:
				break;
		}
	}

	sleep_for_milliseconds(50);
	return action;
}

void GAME_charControler::place_character_randomly(Character* ch)
{
	SharedPtr<Place> place_here = g->levelActive->field[0][0];
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

	std::vector<SharedPtr<Item>> *items = ch->get_staysOn()->get_itemsHere_ptr();
	if (items->size() == 0)
	{
		LOG("NO ITEMS HERE"); // add in game message
	}
	else
	{
		std::vector<int> pickedIndexes = UI::pickUp_items_selector(items);

		std::vector<SharedPtr<Item>> picked = get_vect_items_from_indexes(*items, pickedIndexes);
		for (SharedPtr<Item> item : picked)
		{
			ch->pick_item(item);
			ch->get_staysOn()->pick_up(item);
		}
	}
}




void GAME_charControler::player_inventory_control()
{
	int choosenIndex = 0;
	const std::vector<SharedPtr<Item>>* inventory = g->player->get_inventory_ref();
	while (choosenIndex != -1)
	{
		choosenIndex = UI::player_inventory_selector(inventory);

		if (choosenIndex != -1)
		{
			item_options_control((*inventory)[choosenIndex]);
		}
	}
}


void GAME_charControler::player_equipment_control()
{
	const SharedPtr<Item>* eq = g->player->get_equipped_ref();
	const std::vector<SharedPtr<Item>>* inv = g->player->get_inventory_ref();

	BodyPart choosenBodyPart = UI::player_equipment_selector(eq);
	int choosenEqIndex = static_cast<int>(choosenBodyPart);

	if (choosenEqIndex != -1)
	{
		if (eq[choosenEqIndex] != nullptr)
		{
			item_options_control(eq[choosenEqIndex]);
		}
		else
		{
			int choosenInvIndex = UI::equip_from_inv_selector(choosenBodyPart, inv);
			if (choosenInvIndex != -1)
				g->player->equip_item((*inv)[choosenInvIndex], choosenBodyPart);			
		}
	}
}

void GAME_charControler::item_options_control(SharedPtr<Item> item)
{
	ItemOpt choosenOpt = UI::item_options_selector(item);

	switch (choosenOpt)
	{
	case ItemOpt::look:
		; // info about obj

		break;
	case ItemOpt::equip:
	{
		BodyPart bodypart = UI::choose_bodyPart_to_equip(item, g->player->get_equipped_ref());
		g->player->equip_item(item, bodypart);
		break;
	}
	case ItemOpt::unequip:
	{
		BodyPart bodypart = item->get_wornOnBodyPart();
		g->player->un_equip_item(item, bodypart);
		break;
	}
	case ItemOpt::drop:
		if (item->get_isWorn())
			g->player->un_equip_item(item, item->get_wornOnBodyPart());
		g->player->drop_item(item);
		break;
	case ItemOpt::use:
		// use
		break;
	}
}