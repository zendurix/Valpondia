#include "pch.h"
#include "MENU.h"

MENU::MENU(sf::RenderWindow* window, sf::Text text)
	: windowHandle(window), text(text)
{
	////
}
MENU::~MENU() {}

MENUopt MENU::show_menu_ret_opt()
{
	if (DEBUG_MENU)
	{
		text.setString
		(
			"     ---MENU--- \n"
			" 1 - make random cave map \n"
			" 2 - make random dungeon map \n"
			" 3 - NEW GAME\n"
			" 4 - controls \n"
			" 5 - credits \n"
			" 6 - DEBUG OPTIONS \n"
			" space in game - go back to menu \n"
			" ESC - exit game\n"
		);
		windowHandle->clear();
		windowHandle->draw(text);
		windowHandle->display();

		char option;

		while (1)
		{
			option = Input::user_input_key();
			switch (option)
			{
			case '1':			return MENUopt::caveShow;
			case '2':			return MENUopt::dungShow;
			case '3':			return MENUopt::gameSTART;
			case '4':			return MENUopt::controls;
			case '5':			return MENUopt::credits;
			case '6':			return MENUopt::debugOPT;
			case STD_ESC:		return MENUopt::exitOPT;
			default:			return MENUopt::placeHolder;
			}
		}
	}

	else // Better looking menu
	{
		std::vector<MyText> options =
		{
			strCol("make random cave map", sf::Color::White),
			strCol("make random cave map with steps", sf::Color::White),
			//strCol("  (press space to go to next step)", sf::Color::White),
			strCol("make random dungeon map", sf::Color::White),
			strCol("make random dungeon map with steps (DELETED)", sf::Color::White),
			strCol("test Field Of View on random cave map (play game)", sf::Color::White),
			strCol("controls", sf::Color::White),
			strCol("credits", sf::Color::White),
			strCol("DEBUG OPTIONS ", sf::Color::White),
			strCol(" space in game - go back to menu", sf::Color::White),
			strCol(" ESC - exit game", sf::Color::White)
		};
		MyText title = strCol("     ---MENU--- \n", MCOL::hotPink);

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
			case   1:	return MENUopt::caveShow;
			case   2:	return MENUopt::dungShow;
			case   3:	return MENUopt::gameSTART;
			case   4:	return MENUopt::controls;
			case   5:	return MENUopt::credits;
			case   6:	return MENUopt::debugOPT;
			case  -1:	return MENUopt::exitOPT;
			default:	return MENUopt::placeHolder;
			}
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