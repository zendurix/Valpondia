#include "pch.h"

#include "CONFIGURATION.h"
#include "MapFunctions.h"
#include "Input.h"
#include "MENU.h"
#include "GAME.h"

#include "Items.h"

const lvType startLevel = cave;

bool MENU_handler_ret_startGame(GAME* game, MENU menu, bool* exit);
void MENU_DEBUG_handler(GAME* game, MENU menu);

int main()
{
	sf::Event event;
	char characterInput;
	bool wait = true;
	bool startGame = false;
	bool EXIT = false;

	MyText initit;
	GAME* game = GAME::getInstance();	
	sf::RenderWindow window(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Project");
	game->setWindow(&window);
	Input::init_Input(&window);
		


	UI::init_UI(&window);
	LOG_NEW;
	sf::Font* font= new sf::Font;
	font->loadFromFile("../res/fonts/DOSfont.ttf");

	sf::Music mainTheme;
	mainTheme.openFromFile("../res/ost/Candle Flame.ogg");

	sf::Text* text = init_text();

	MENU menu(&window, *text);
	   	    

	SharedPtr<Item> swordHilt = std::make_shared<Item>(Items::swordHilt);
	   	 

	while (window.isOpen()) // MENU LOOP
	{		

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		//game->levelActive->RESET_field();
		startGame = MENU_handler_ret_startGame(game, menu, &EXIT);

		if (startGame) 
		{	// SET GAME

			LOG_NEW;
			game->player = new CharacterPlayer(3, 25, &game->levelActive->field);
			//game->CharControler->place_character_randomly(game->player);
			game->unmake_visible_whole_level();
			game->reset_visibility(*game->player);
			game->Printer->print_field_UPDATE();
			//mainTheme.play();
			wait = true;

			
			while (wait) /////////////////////////////////////////////////// GAME LOOP
			{
				characterInput = game->CharControler->player_turn();

				game->unmake_visible_whole_level();
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



















bool MENU_handler_ret_startGame(GAME* game, MENU menu, bool* exit)
{
	MENUoptions MENUopt = menu.show_menu_ret_opt();

	switch (MENUopt)
	{
	case caveShow:
		game->levelActive->changeLevelType(cave);			
		game->Printer->print_field();
		Input::wait_for_input(inputType::space);
		return false;
//	case caveStep:
//		CA_cave_gen::make_cave_map(game->levelActive->field, true);
//		return false;
	case dungShow:
		game->levels[game->levelActiveId]->changeLevelType(dungeon);
		game->Printer->print_field();
		Input::wait_for_input(inputType::space);
		return false;
//	case dungStep:
//		//make_dung_map_ret_rooms(true);
//		return false;
	case gameSTART:
		//game->levels[game->levelActiveId]->changeLevelType(ruins);
		return true;
	case controls:
		menu.show_controls();
		return false;
	case credits:
		menu.show_credits();
		return false;
	case debugOPT:  
		MENU_DEBUG_handler(game, menu);
		return false;
	case exitOPT:
		*exit = true;
		return false;
	default:
		return false;
	}
}


void MENU_DEBUG_handler(GAME* game, MENU menu)
{
	bool loop = true;
	char option;

	menu.show_debug_options();

	while (loop)
	{
		option = Input::user_input_key();
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