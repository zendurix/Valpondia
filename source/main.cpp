#include "pch.h"

#include "CONFIGURATION.h"
#include "GAME.h"
#include "GAME_Printer.h"
#include "Input.h"



int main()
{	
	sf::RenderWindow window(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Project");

	Input::init_Input(&window);

	GAME* game = GAME::getInstance();
	game->setWindow(&window);

	Entity player = game->make_player();


	game->reset_visibility(player);
	game->Printer->print_field();


	while (1)
	{

		game->ecs->update_all_systems();
		game->ecs->clear_events();

		game->reset_visibility(player);

		game->Printer->print_field();
	}




	std::cin.get();

	GAME::DELETEinstance();
	return 0;
}

