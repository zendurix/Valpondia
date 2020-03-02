#include "pch.h"
#include "GAME.h"

#include "GAME_Printer.h"
#include "GAME_Factory.h"
#include "general_purpose_func.h"
#include "Level.h"
#include "Place.h"
#include "Input.h"
#include "FieldOfView.h"
#include "PathFinding.h"


GAME* GAME::getInstance()
{ // only one instance of GAME can exist, and then this function cann't be called
	if (instance == nullptr)
	{
		LOG_NEW;
		instance = new GAME();
		return instance;
	}
	else return nullptr;
}
void GAME::DELETEinstance()
{
	delete GAME::instance;
}

GAME::GAME()
{
	levelActive = nullptr;
	init();
	LOG("GAME...............................created");



	make_level(Connector{ -1, -1, 0, ' ' });
	LOG("Level..........................initialized");
}

GAME::~GAME()
{
	//delete player;
	//for (Level lev : levels)
	//{
	//	delete lev;
	//}

	//delete CharControler;


	//delete Printer;
}





void GAME::init()
{
	Printer = new GAME_Printer(*this);
	Factory = new GAME_Factory(*this, &Printer->textures);

	ecs = std::make_unique<ECS>();

	ecs->init();
	LOG("ECS System.........................initialized")
	ecs->register_components();
	ecs->register_systems();

	Place::set_ecsRef(ecs);
	Place::set_def_floor_sprite(std::make_shared<sf::Sprite>(Printer->textures[static_cast<int>(TextureType::floorTile)]));
	Place::set_textures(&Printer->textures, &Printer->texturesASCII);

	System::set_gamePtr(this);

}

void GAME::setWindow(sf::RenderWindow* windowPtr)
{
	windowHandle = windowPtr;
}






Entity GAME::make_player()
{
	Position pos{ 20, 25, 0 };
	Entity newPlayer = ecs->create_entity();
	ecs->add_component(newPlayer, Player{});
	ecs->add_component(newPlayer, pos);
	ecs->add_component(newPlayer, Actor{});
	ecs->add_component(newPlayer, Name{ strCol("Zendurix", sf::Color::White) });
	SharedPtr<sf::Sprite> playerSprite = std::make_shared<sf::Sprite>(Printer->textures[static_cast<int>(TextureType::player)]);
	ecs->add_component(newPlayer, Render{ playerSprite, sf::Color::Green });
	ecs->add_component(newPlayer, Vision{ 30 });

	levelActive->get_fieldRef()[pos.y][pos.x]->go_here(newPlayer);

	ecs->signature_changed(newPlayer, ecs->get_signature(newPlayer));


	player = newPlayer;
	return newPlayer;
}









void GAME::reset_visibility(Entity entity)
{
	Position pos = ecs->get_component<Position>(entity);
	int viewDist = ecs->get_component<Vision>(entity).viewDistance;

	SharedPtr<Place> entityPlace = levels[pos.levelID]->get_fieldRef()[pos.y][pos.x];

	unmake_visible_whole_level();

	FieldOfView::update_view(&levelActive->get_fieldRef(), entityPlace, viewDist);

	entityPlace->make_visible();

	//for (int i = 0; i < MYHEIGHT; i++)
	//{
	//	for (int j = 0; j < MYLENGTH; j++)
	//	{
	//		levelActive->get_fieldRef()[i][j]->set_wasCheck(false);
	//		if (levelActive->field[i][j]->get_wasVisible() && !levelActive->field[i][j]->get_visible())
	//		{
	//			levelActive->field[i][j]->set_wasVisible(false);
	//		}
	//	}
	//}
}


















void GAME::RESET_levels()
{
	for (int i = 1; i <= Level::levelCount; i++)
	{
		delete levels[i];
	}

	levels.resize(1);
	levels.shrink_to_fit();

	Level::levelCount = 0;
	levelActive = levels[0];

	//levelActive->stairsDown->set_stairsDown(false);

	//player->set_onLevelID(0);  MDELETE
	//player->set_fieldArr(&levelActive->field); MDELETE
}













void GAME::unmake_visible_whole_level()
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			levelActive->field[i][j]->unmake_visible();
		}
	}
}





void GAME::make_level(Connector connector)
{
	static std::vector<int> levelsMade;
	Level* newLevel;
	Place::RESET_counters();

	auto makeLevel0 = [&]()
	{
		LvType levelType = LEVEL_ORDER[0].first;
		std::string fileName = LEVEL_ORDER[0].second;

		newLevel = new Level(levelType, 0, nullptr, fileName);

		newLevel->get_stairsDown()->set_connector(Connector{ -1, -1, 2, '-', true });

		newLevel->field[23][0]->set_connector(Connector{ -1, -1, -10, '4' });
		newLevel->field[24][0]->set_connector(Connector{ -1, -1, -10, '4' });
		newLevel->field[25][0]->set_connector(Connector{ -1, -1, -10, '4' });
		newLevel->field[26][0]->set_connector(Connector{ -1, -1, -10, '4' });

		newLevel->field[23][69]->set_connector(Connector{ 23, 0, 1, '6' });
		newLevel->field[24][69]->set_connector(Connector{ 24, 0, 1, '6' });
		newLevel->field[25][69]->set_connector(Connector{ 25, 0, 1, '6' });
		newLevel->field[26][69]->set_connector(Connector{ 26, 0, 1, '6' });

	};

	auto makeLevel1 = [&]()
	{
		LvType levelType = LEVEL_ORDER[1].first;
		std::string fileName = LEVEL_ORDER[1].second;

		newLevel = new Level(levelType, 0, levelActive->stairsDown, fileName);

		newLevel->field[23][0]->set_connector(Connector{ 23, 69, 0, '4' });
		newLevel->field[24][0]->set_connector(Connector{ 24, 69, 0, '4' });
		newLevel->field[25][0]->set_connector(Connector{ 25, 69, 0, '4' });
		newLevel->field[26][0]->set_connector(Connector{ 26, 69, 0, '4' });

	};

	auto makeLevel2 = [&]()
	{
		LvType levelType = LEVEL_ORDER[2].first;
		std::string fileName = LEVEL_ORDER[2].second;
		newLevel = new Level(levelType, 1, levels[0]->stairsDown);

		newLevel->get_stairsUp()->set_connector(
			Connector{ levels[0]->get_stairsDown()->get_y(), levels[0]->get_stairsDown()->get_x(), 0, '+',  false, true });
		levels[0]->get_stairsDown()->set_connector(
			Connector{ newLevel->get_stairsUp()->get_y(), newLevel->get_stairsUp()->get_x(), 2,  '-', true });

	};





	if (!vector_contains(levelsMade, connector.destinationLevel))
	{
		int destLv = connector.destinationLevel;
		switch (destLv)
		{
		case 0:
		{
			makeLevel0();
		}
		break;
		case 1:
		{
			makeLevel1();
		}
		break;
		case 2:
		{
			if (!vector_contains(levelsMade, 1))
			{
				makeLevel1();
				levels.push_back(newLevel);
				levelsMade.push_back(destLv);
			}
			Place::RESET_counters();
			makeLevel2();
		}
		break;



		default:
			LOG("ERROR: wrong level ID " << connector.destinationLevel);
			break;


		}


		levels.push_back(newLevel);
		levelsMade.push_back(destLv);
	}


	levelActive = levels[connector.destinationLevel];

}




