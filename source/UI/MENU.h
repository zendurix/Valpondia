#pragma once

#include "../CONFIGURATION.h"


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
};

