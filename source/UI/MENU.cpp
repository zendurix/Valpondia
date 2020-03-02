#include "pch.h"
#include "MENU.h"

#include "../general_purpose_func.h"
#include "../Input.h"
#include "UIWindow.h"
#include "MyText.h"


MENU::MENU(sf::RenderWindow* window, sf::Text text)
	: windowHandle(window), text(text)
{}
MENU::~MENU() {}

MENUopt MENU::show_menu_ret_opt()
{
	std::vector<MyText> options =
	{
		//strCol("make random cave map", sf::Color::White),
		//strCol("make random cave map with steps", sf::Color::White),
		//strCol("  (press space to go to next step)", sf::Color::White),
		//strCol("make random dungeon map", sf::Color::White),
		//strCol("make random dungeon map with steps (DELETED)", sf::Color::White),
		strCol("PLAY GAME", sf::Color::White),
		strCol("controls", sf::Color::White),
		strCol("credits", sf::Color::White),
		//strCol("DEBUG OPTIONS ", sf::Color::White),
		strCol( "EXIT", sf::Color::White)
	};
	MyText title = strCol("---MENU---\n", MCOL::hotPink);

	int x = 0;
	int y = 0;
	int winLength = WIN_LENGTH;
	int winHeight = WIN_HEIGHT;
	int charHeight = title.get_charHeight();

	UIWindow UIwin(winLength, winHeight, x, y, title, options, charHeight, false, 10);

	while (1)
	{
		// UIwin ret 0 as first, but here 1 is first
		int choosenOpt = UIwin.call_window_return_choosen_indexes(windowHandle)[0] + 1;
		switch (choosenOpt)
		{
		case   1:	return MENUopt::gameSTART;
		case   2:	return MENUopt::controls;
		case   3:	return MENUopt::credits;
		case   4:	return MENUopt::exitOPT;
		default:	return MENUopt::placeHolder;
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
		" - - move level down (on stairs down - yellow tile)\n"
		" + - move level up (on stairs up - red tile)\n"
		" p - pick up item\n"
		" space - choose items to pick\n"
		" enter - take choosen items\n"
		" tab - take all items\n\n"
		" space in game - go back to menu\n"
		" press space to exit.."
	);
	windowHandle->clear();
	windowHandle->draw(text);
	windowHandle->display();

	Input::wait_for_input(inputType::space);
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

	Input::wait_for_input(inputType::space);
}


