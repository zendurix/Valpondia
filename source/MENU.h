#pragma once

#include "general_purpose_func.h"
#include "Input.h"
#include "UIWindow.h"
#include "MyText.h"

enum MENUoptions { placeHolder = 0, caveShow = 1, dungShow, gameSTART,
					controls, credits, debugOPT, exitOPT};

class MENU
{
private:
	sf::RenderWindow* windowHandle;
	sf::Text text;

public:
	MENU(sf::RenderWindow* window, sf::Text text);
	~MENU();


	MENUoptions show_menu_ret_opt();
	void show_controls();
	void show_credits();
	void show_debug_options();
};

