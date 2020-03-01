#pragma once

#include "general_purpose_func.h"
#include "Input.h"
#include "UIWindow.h"
#include "MyText.h"



class MENU
{
private:
	sf::RenderWindow* windowHandle;
	sf::Text text;

public:
	MENU(sf::RenderWindow* window, sf::Text text);
	~MENU();


	MENUopt show_menu_ret_opt();
	void show_controls();
	void show_credits();
	void show_debug_options();
};

