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
			//g->make_new_level();
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
	char action = Input::user_input_key();

	bool finish = false;

	Connector& connector = g->player->get_staysOn()->connector;
	if (connector.levelDestination == -10)
	{
		if (action == connector.pushToGo)
		{
			LOG("YOU WALK AWAY FROM YOUR DESTINY...");
			finish = true;
		}
	}
	else if (connector.levelDestination != -1)
	{

		if (action == connector.pushToGo)
		{
			finish = true;
			if (connector.destination == nullptr)
				g->make_level(connector);

			move_to_level(g->player, connector);


		}


	}

	if (!finish && action >= '0' && action <= '9')
	{
		Character* attackThis = g->player->move_and_attack(action);
		if (attackThis != nullptr)
			attack(g->player, attackThis);
	}
	else if (!finish)
	{
		// to duplicate game state on both windows - to avoid background to "UI's" windows flickering
		g->Printer->print_field_UPDATE();

		switch (action)
		{
			case '+':
			{
				//if (g->player->get_staysOn()->get_stairsUp())
				//	move_level_up(g->player);
				if (g->levelActive->get_stairsUp() != nullptr && g->levelActive->get_stairsUp()->get_wasSeen())
				{ // go to stairs up if visible
					char dir = PathFinding::best_dir(&g->levelActive->field, *g->player, g->levelActive->get_stairsUp());
					g->player->move_and_attack(dir);
				}
				break;
			}
			case '-':
			{
				//if (g->player->get_staysOn()->get_stairsDown())
				//	move_level_down(g->player);
				if (g->levelActive->get_stairsDown() != nullptr && g->levelActive->get_stairsDown()->get_wasSeen())
				{ // go to stairs down if visible
					char dir = PathFinding::best_dir(&g->levelActive->field, *g->player, g->levelActive->get_stairsDown());
					g->player->move_and_attack(dir);
				}
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

	BodyPart choosenBodyPart;
	int choosenEqIndex;

	do
	{
		choosenBodyPart = UI::player_equipment_selector(eq);
		choosenEqIndex = static_cast<int>(choosenBodyPart);	
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
	} while (choosenEqIndex != -1);
}

void GAME_charControler::item_options_control(SharedPtr<Item> item)
{
	ItemOpt choosenOpt = UI::item_options_selector(item);

	switch (choosenOpt)
	{
	case ItemOpt::look:
		UI::show_item_info(item);
		break;
	case ItemOpt::equip:
	{
		BodyPart bodypart = UI::choose_bodyPart_to_equip(item, g->player->get_equipped_ref());
		if (bodypart != BodyPart::none)
		{
			g->player->equip_item(item, bodypart);
		}
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
	case ItemOpt::none:
		break;
	}
}






void GAME_charControler::attack(Character* attacker, Character* defender)
{
	if (defender->do_dodge() == true)
	{
		LOG(defender->get_name() << " dodged");
	}
	else 
	{
		DMG attackerDMG = attacker->do_attack();
		DEF defenderDEF = defender->do_defend();

		bool penetrated = (attackerDMG.penetration >= defenderDEF.baseDEF);
		if (penetrated)
		{
			int dmgToArmor = attackerDMG.baseDMG - defenderDEF.baseDEF;
			// deal dmg to armor
			int dmgToDefender = attackerDMG.baseDMG;
			// dmgToDefender -= dmgToArmor; // moze jednak gupi pomysl z tym
			int fireDmg = attackerDMG.fireDMG - defenderDEF.fireDEF;

			dmgToDefender += fireDmg;

			defender->take_damage(dmgToDefender);

			LOG(attacker->get_name() << " hit " << defender->get_name() << " for " << dmgToDefender << " dmg");
		}
		else // not penetrated
		{
			int fireDmg = attackerDMG.fireDMG - defenderDEF.fireDEF;
			defender->take_damage(fireDmg);

			// and dmg to weapon and armor

			LOG(attacker->get_name() << " didn't penetrate " << defender->get_name() << " armor");
		}

	}





}






void GAME_charControler::move_to_level(Character* ch, Connector connector)
{
	g->levelActiveId = connector.levelDestination;
	g->levelActive = g->levels[g->levelActiveId];
	ch->set_onLevelID(g->levelActiveId);

	
	
	ch->set_fieldArr(&g->levelActive->field);
	ch->set_staysOn(connector.destination);
	
	g->levelActive->field[ch->get_y()][ch->get_x()]->go_here(ch);
	

}