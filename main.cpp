#include "pch.h"

#include "CONFIGURATION.h"
#include "UI/MENU.h"
#include "GAME.h"
#include "general_purpose_func.h"
#include "Input.h"
#include "MAP_GEN/MapGen.h"
#include "Place.h"



int main()
{	

	sf::RenderWindow window(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Project");

	Input::init_Input(&window);

	GAME* game = GAME::getInstance();
	game->setWindow(&window);

	MapGen::set_gamepTr(game);

	Entity player = game->make_player();

	MENU menu(&window, *init_text());
	MENUopt option;


	sf::Music robo;
	robo.openFromFile("../res/ost/robo.ogg");
	//robo.play();


	do
	{
		option = menu.show_menu_ret_opt();

		switch (option)
		{
		case MENUopt::gameSTART:
			{
				bool backToMenu = false;
				game->reset_visibility(player);
				//game->Printer->print_field();

				//game->make_level(Place::NULLConnector, true);

				while (!backToMenu)   // GAME LOOP ////////////////////////////
				{
					game->ecs->update_entity_systems(player);

					game->ecs->clear_events();

					game->reset_visibility(player);

					game->Printer->print_field_with_camera(game->ecs->get_component<Position>(player));

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

