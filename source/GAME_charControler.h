#pragma once
// component of GAME class, responsible for making actions and managing characters (AI and player)

#include "GAME.h"
#include "Input.h"
#include "UI.h"
#include "FieldOfView.h"

class GAME;

class GAME_charControler
{
friend GAME;
private:
	GAME* g;
	GAME_charControler(GAME* game);
	~GAME_charControler();

public:
	char player_turn();
	void place_character_randomly(Character* ch);
	void move_level_down(Character* ch);
	void move_level_up(Character* ch);
	void pick_up_item(Character* ch);
	void player_inventory_control();
	void player_equipment_control();
	void item_options_control(SharedPtr<Item> item);
};

