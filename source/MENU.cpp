#include "pch.h"
#include "MENU.h"

MENU::MENU(sf::RenderWindow* window, sf::Text text)
{
	this->windowHandle = window;
	this->text = text;
}
MENU::~MENU()
{

}

MENUoptions MENU::show_menu_ret_opt()
{
	GAME* game = GAME::getInstance();

	text.setString
	(
		"     ---MENU--- \n"
		" 1 - make random cave map \n"
		" 2 - make random cave map with steps \n"
		"     (press space to go to next step)\n"
		" 3 - make random dungeon map \n"
		" 4 - make random dungeon map with steps\n"
		" 5 - test Field Of View on random cave map (play game)\n"
		" 6 - controls \n"
		" 7 - credits \n"
		" 8 - DEBUG OPTIONS \n"
		" space in game - go back to menu \n"
		" ESC - exit game\n"
	);
	windowHandle->clear();
	windowHandle->draw(text);
	windowHandle->display();

	char option;
	
	while(1)
	{
		option = user_input_key();
		switch (option)
		{
		case '1':			return caveShow;
		case '2':			return caveStep;
		case '3':			return dungShow;
		case '4':			return dungStep;
		case '5':			return gameSTART;
		case '6':			return controls;
		case '7':			return credits;
		case '8':			return debugOPT;
		case STD_ESC:		return exitOPT;
		default:			return placeHolder;
		}
	}

}

void MENU::show_controls()
{
	text.setString
	(
		"   ---MOVEMENT--- \n"
		"  Turn numLock on!! \n"
		" 7   8  9 \n"
		"   \\ | /    \n"
		" 4 - @ - 6 \n"
		"   / | \\    \n"
		" 1   2   3 \n"
		" 5 - wait turn \n"
		"\n   ---alternate movement without numPad--- \n"
		" q   ^  e \n"
		"   \\ | /    \n"
		" < - @ - > \n"
		"   / | \\    \n"
		" a   \\/   d \n"
		" ^, \\/, <, > : up, down, left, right arrows \n\n"
		" - - move level down (on stairs down - yellow tile)\n"
		" + - move level up (on stairs up - red tile)\n"
		" p - pick up item\n"
		" space - choose items to pick\n"
		" enter - take choosen items\n"
		" tab - take all items\n\n"
		" press space to exit.."
	);
	windowHandle->clear();
	windowHandle->draw(text);
	windowHandle->display();

	wait_for_input(space);
}

void MENU::show_credits()
{
	text.setString
	(
		"   ---CREDITS---\n"
		" game design and programming : Michal Majda \n"
		" graphics                    : Michal Majda \n"
		" music                       : Michal Warzymlot \n\n"
		" press space to exit.."
	);
	windowHandle->clear();
	windowHandle->draw(text);
	windowHandle->display();

	wait_for_input(space);
}


void MENU::show_debug_options()
{
	text.setString
	(
		"   ---DEBUG OPTIONS---\n"
		" 1 - make cave map 100 times	\n"
		" 2 - make dungeon map 100 times    \n"
		" space - back to MENU"
	);
	windowHandle->clear();
	windowHandle->draw(text);
	windowHandle->display();
}