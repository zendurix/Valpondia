#include "pch.h"

#include "CONFIGURATION.h"
#include "MapFunctions.h"
#include "MENU.h"
#include "GAME.h"

#include "Items.h"

const lvType startLevel = cave;

bool MENU_handler_ret_startGame(MENU menu, bool* exit);
void MENU_DEBUG_handler(MENU menu);

int main()
{
	MyText initit;
	//STD_FONT = new sf::Font;
	//STD_FONT->loadFromFile("../SFML/sources/DOSfont.ttf");



	//static MyText mm = MyText();



	GAME* game = GAME::getInstance();
	game->make_new_level(cave); // for first level initializing
	
	sf::RenderWindow window(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Project");
	game->setWindow(&window);
		
	LOG_NEW;
	game->player = new CharacterPlayer(2, 2, &game->levelActive->field);

	UI::init_UI(&window, game->player);


	
	//UI::player_inventory_window();


	LOG_NEW;
	sf::Font* font= new sf::Font;
	font->loadFromFile("../SFML/sources/DOSfont.ttf");






	sf::Music mainTheme;
	mainTheme.openFromFile("../SFML/sources/Candle Flame.ogg");

	sf::Text* text = init_text();

	MENU menu(&window, *text);


	char characterInput;
	bool wait = true;
	bool startGame = false;
	bool EXIT = false;


	MyText aa = Items::steelSword.get_name();


	SharedPtr<Item> sword = std::make_shared<Item>(Items::steelSword);
	SharedPtr<Item> helmet = std::make_shared<Item>(Items::cardboardHelmet);
	SharedPtr<Item> sword1 = std::make_shared<Item>(Items::steelSword);
	SharedPtr<Item> helmet1 = std::make_shared<Item>(Items::cardboardHelmet);
	SharedPtr<Item> trousers = std::make_shared<Item>(Items::rubberTrousers);
	SharedPtr<Item> sword2h = std::make_shared<Item>(Items::steelSword2h);
	SharedPtr<Item> swordHilt = std::make_shared<Item>(Items::swordHilt);
	game->player->pick_item(swordHilt);
	//sword.melee.hit();



	CharacterEnemy goblin1(4, 6, &game->levelActive->field);




	while (window.isOpen()) // MENU LOOP
	{		
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();


		game->levelActive->RESET_field();
		startGame = MENU_handler_ret_startGame(menu, &EXIT);
		



		if (startGame) // SET GAME
		{
			game->CharControler->place_character_randomly(game->player);

			PathFinding::set_fieldRef(&game->levelActive->field);

			game->CharControler->place_character_randomly(&goblin1);

			game->levelActive->set_true_all_changedPrint();

			game->unmake_visible_whole_level();
			game->reset_visibility(*game->player, goblin1);
			game->Printer->print_field_UPDATE();
			//mainTheme.play();
			wait = true;

			game->levelActive->field[10][10]->drop_here(helmet);
			game->levelActive->field[10][10]->drop_here(sword);
			game->levelActive->field[10][10]->drop_here(helmet1);
			game->levelActive->field[10][10]->drop_here(sword1);
			game->levelActive->field[10][10]->drop_here(trousers);

			game->levelActive->field[13][13]->drop_here(sword2h);

			while (wait) /////////////////////////////////////////////////// GAME LOOP
			{
				for (int i = 0; i < 1; i++)
				{
					characterInput = game->CharControler->player_turn();
					game->Printer->print_field_UPDATE();
				}

				if (game->levelActiveId == 0)
				{
					goblin1.follow_target_Astar(game->player->get_staysOn());
				}

				game->unmake_visible_whole_level();
				if (game->levelActiveId == 0)
				{
					game->reset_visibility(*game->player, goblin1);
				}
				else
					game->reset_visibility(*game->player);

				game->Printer->print_field_UPDATE();				


				if (characterInput == ' ')
				{
					wait = false;
					game->RESET_levels();
					mainTheme.stop();
				}
			}   /////////////////////////////////////////////////// END OF GAME LOOP

		}


		if (EXIT)
			window.close();

		window.clear();		
	}
	
	GAME::DELETEinstance();
	return 0;
}







bool MENU_handler_ret_startGame(MENU menu, bool* exit)
{
	GAME* game = GAME::getInstance();
	MENUoptions MENUopt = menu.show_menu_ret_opt();

	switch (MENUopt)
	{
	case caveShow:
		game->levelActive->changeLevelType(cave);			
		game->Printer->print_field();
		wait_for_input(space);
		return false;
	case caveStep:
		make_cave_map(true, game->levelActive->field);
		return false;
	case dungShow:
		game->levels[game->levelActiveId]->changeLevelType(dungeon);
		game->Printer->print_field();
		wait_for_input(space);
		return false;
	case dungStep:
		make_dung_map_ret_rooms(true);
		return false;
	case gameSTART:
		game->levels[game->levelActiveId]->changeLevelType(startLevel);
		return true;
	case controls:
		menu.show_controls();
		return false;
	case credits:
		menu.show_credits();
		return false;
	case debugOPT:  
		MENU_DEBUG_handler(menu);
		return false;
	case exitOPT:
		*exit = true;
		return false;
	default:
		return false;
	}
}


void MENU_DEBUG_handler(MENU menu)
{
	GAME* game = GAME::getInstance();
	bool loop = true;
	char option;

	menu.show_debug_options();

	while (loop)
	{
		option = user_input_key();
		switch (option)
		{
		case '1':
			for (int i = 0; i < 100; i++)
			{
				game->levelActive->changeLevelType(cave);
				LOG("CAVE_TEST: " << i);
			}
			break;
		case '2':
			for (int i = 0; i < 100; i++)
			{
				game->levelActive->changeLevelType(dungeon);
				LOG("DUNG_TEST: " << i);
			}
			break;
		case ' ':
			loop = false;
			break;
		default:
			break;
		}
	}
}