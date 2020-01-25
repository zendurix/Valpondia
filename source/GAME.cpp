#include "pch.h"
#include "GAME.h"

GAME* GAME::instance = nullptr;

GAME::GAME()
{
	levelActiveId = -1;
}

GAME* GAME::getInstance()
{
	if (instance == nullptr)
	{
		LOG_NEW;
		instance = new GAME();
		instance->init_components();
	}
	return instance;
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
	LOG_NEW;
	CharControler = new GAME_charControler(this);
}


void GAME::setWindow(sf::RenderWindow* windowPtr)
{
	windowHandle = windowPtr;
}


void GAME::make_new_level(lvType levelType)
{
	levelActiveId++;
	Level* newLevel;
	if (levelActiveId == 0)
	{
		newLevel = new Level(levelType, levelActiveId, nullptr);
		LOG_NEW;
	}
	else
	{
		Place::RESET_counters();
		newLevel = new Level(levelType, levelActiveId, levelActive->stairsDown);
		LOG_NEW;
	}
	levelActive = newLevel;
	newLevel->make_level();
	newLevel->place_stairsDown_random();
	levels.push_back(newLevel);
}

void GAME::reset_visibility(Character character)
{
	//std::vector<std::shared_ptr<Place> > checkAgain;



	
	FieldOfView::update_view(character.get_staysOn());
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


