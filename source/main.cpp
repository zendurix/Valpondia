#include "pch.h"

#include "CONFIGURATION.h"
#include "UI/MENU.h"
#include "GAME.h"
#include "GAME_Printer.h"
#include "GAME_Factory.h"
#include "general_purpose_func.h"
#include "Input.h"



int main()
{	
	sf::RenderWindow window(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Project");

	Input::init_Input(&window);

	GAME* game = GAME::getInstance();
	game->setWindow(&window);

	Entity player = game->make_player();

	MENU menu(&window, *init_text());
	MENUopt option;



	do
	{
		option = menu.show_menu_ret_opt();

		switch (option)
		{
		case MENUopt::gameSTART:
			{
				bool backToMenu = false;
				game->reset_visibility(player);
				game->Printer->print_field();


				Entity rat = game->Factory->make_rat(Position{ 10, 10, 0 });

				while (!backToMenu)   // GAME LOOP ////////////////////////////
				{

					game->ecs->update_all_systems();
					game->ecs->clear_events();

					game->reset_visibility(player);

					game->Printer->print_field();




				}   // END OF GAME LOOP ////////////////////////////
			}
			break;
		case MENUopt::controls:
			menu.show_controls();
			break;
		case MENUopt::credits:
			menu.show_credits();
			break;
		case MENUopt::exitOPT:
			break;
		default:
			break;
		}
			   

	} while (option != MENUopt::exitOPT);





	//std::cin.get();

	GAME::DELETEinstance();
	return 0;
}

