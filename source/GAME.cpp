#include "pch.h"
#include "GAME.h"

GAME* GAME::instance = nullptr;

GAME::GAME()
{
	levelActiveId = -1;
	init_components();
	LOG("GAME...............................created");
	make_level(Connector{ nullptr, ' ', 0 });
	LOG("Level..........................initialized");
}

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

GAME::~GAME()
{
	delete player;
	for (Level* lev : levels)
	{
		delete lev;
	}

	delete CharControler;
	delete Printer;
}

void GAME::DELETEinstance()
{
	delete GAME::instance;
}

void GAME::init_components()
{
	LOG_NEW;
	Printer = new GAME_Printer(this);
	LOG("GAME Printer.......................initialized");
	LOG_NEW;
	CharControler = new GAME_charControler(this);
	LOG("GAME CharControler.................initialized");
}

void GAME::setWindow(sf::RenderWindow* windowPtr)
{
	windowHandle = windowPtr;
}
















void GAME::reset_visibility(Character character)
{	
	FieldOfView::update_view(&levelActive->field, character.get_staysOn());
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			levelActive->field[i][j]->set_wasCheck(false);
			if (levelActive->field[i][j]->get_wasVisible() &&
				!levelActive->field[i][j]->get_visible())
			{
				levelActive->field[i][j]->set_wasVisible(false);
			}
		}
	}	
}
























void GAME::RESET_levels()
{
	for (int i = 1; i <= Level::levelCount; i++)
	{
		delete levels[i];
	}

	levels.resize(1);
	levels.shrink_to_fit();

	levelActiveId = 0;
	Level::levelCount = 0;
	levelActive = levels[0];
	levelActive->stairsDown->set_stairsDown(false);

	player->set_onLevelID(0);
	player->set_fieldArr(&levelActive->field);
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
		lvType levelType = LEVEL_ORDER[0].first;
		std::string fileName = LEVEL_ORDER[0].second;
		levelsMade.push_back(0);

		newLevel = new Level(levelType, 0, nullptr, fileName);
		newLevel->make_level();

		newLevel->get_stairsDown()->connector = Connector{ nullptr, '-', 2 };

		newLevel->field[23][0]->connector = Connector{ nullptr, '4', -10 };
		newLevel->field[24][0]->connector = Connector{ nullptr, '4', -10 };
		newLevel->field[25][0]->connector = Connector{ nullptr, '4', -10 };
		newLevel->field[26][0]->connector = Connector{ nullptr, '4', -10 };


		newLevel->field[23][69]->connector = Connector{ nullptr, '6', 1 };
		newLevel->field[24][69]->connector = Connector{ nullptr, '6', 1 };
		newLevel->field[25][69]->connector = Connector{ nullptr, '6', 1 };
		newLevel->field[26][69]->connector = Connector{ nullptr, '6', 1 };

		levels.push_back(newLevel);
	};

	auto makeLevel1 = [&]()
	{
		lvType levelType = LEVEL_ORDER[1].first;
		std::string fileName = LEVEL_ORDER[1].second;
		levelsMade.push_back(1);

		newLevel = new Level(levelType, 0, levelActive->stairsDown, fileName);
		newLevel->make_level();

		newLevel->field[23][0]->connector = Connector{ levels[0]->field[23][69], '4', 0 };
		newLevel->field[24][0]->connector = Connector{ levels[0]->field[24][69], '4', 0 };
		newLevel->field[25][0]->connector = Connector{ levels[0]->field[25][69], '4', 0 };
		newLevel->field[26][0]->connector = Connector{ levels[0]->field[26][69], '4', 0 };

		levels[0]->field[23][69]->connector = Connector{ newLevel->field[23][0], '6', 1 };
		levels[0]->field[24][69]->connector = Connector{ newLevel->field[24][0], '6', 1 };
		levels[0]->field[25][69]->connector = Connector{ newLevel->field[25][0], '6', 1 };
		levels[0]->field[26][69]->connector = Connector{ newLevel->field[26][0], '6', 1 };

		levels.push_back(newLevel);
	};

	auto makeLevel2 = [&]()
	{
		lvType levelType = LEVEL_ORDER[2].first;
		std::string fileName = LEVEL_ORDER[2].second;
		levelsMade.push_back(2);
		newLevel = new Level(levelType, 1, levels[0]->stairsDown);
		newLevel->make_level();

		newLevel->get_stairsUp()->connector = Connector{ levels[0]->get_stairsDown(), '+', 0 };
		levels[0]->get_stairsDown()->connector = Connector{ newLevel->get_stairsUp(), '-', 2 };

		levels.push_back(newLevel);

	};






	switch (connector.levelDestination)
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
			makeLevel1();

		Place::RESET_counters();
		makeLevel2();			

	}
		break;



	default:
		LOG("ERROR: wrong level ID " << connector.levelDestination);
		break;


	}


	levelActive = newLevel;


}




