#include "pch.h"
#include "Level.h"



Level::Level(lvType p_levelType, int depthLevel, SharedPtr<Place>  stairsDown, std::string fileName)
	: mapFileName(fileName)
{
	levelCount++;
	init_field();
	depth = depthLevel;
	levelID = levelCount;
	levelType = p_levelType;
	prevStairsDown = stairsDown;
}


Level::~Level()
{
}

void Level::init_field()
{
	field.reserve(MYHEIGHT);
	for (std::vector <SharedPtr<Place> > x : field)
	{
		x.reserve(MYLENGTH);
	}

	for (int i = 0; i < MYHEIGHT; i++)
	{
		std::vector <SharedPtr<Place> > fieldRow;
		for (int j = 0; j < MYLENGTH; j++)
		{
			fieldRow.push_back(std::make_shared<Place> (levelID));
		}
		field.push_back(fieldRow);
	}
}

void Level::make_level()
{
	do
	{
		if (levelType == ruins)
		{
			make_map_ruins(*this);
		}
		else if (levelType == cave)
		{
			CA_cave_gen::make_cave_map(field);
		}
		else if (levelType == dungeon)
		{
			rooms =	BspMapGen::make_dung_map_ret_rooms(field, MAX_LEVEL);
		}
		else if (levelType == fromFile)
		{
			load_map_from_file(*this, mapFileName);
		}
		
	} while (!isPlaceForStairsUp());

	if (depth != 0)
	{
		field[prevStairsDown->get_y()][prevStairsDown->get_x()]->set_stairsUp(true);
		stairsUp = field[prevStairsDown->get_y()][prevStairsDown->get_x()];
	}
}







bool Level::isPlaceForStairsUp()
{
	if (depth != 0)
	{
		if (levelType == cave)
		{
			if (field[prevStairsDown->get_y()][prevStairsDown->get_x()]->get_isObstacle())
				return false;
			else
				return true;
		}
		else if (levelType == dungeon)
		{
			if (field[prevStairsDown->get_y()][prevStairsDown->get_x()]->get_isInRoom())
				return true;
			else
				return false;
		}
	}
	else
	{
		return true;
	}
}

void Level::changeLevelType(lvType levelType)
{
	this->levelType = levelType;
	rooms.clear();
	switch (levelType)
	{
	case ruins:
		RESET_field();
		make_map_ruins(*this);
		break;
	case cave:
		CA_cave_gen::make_cave_map(field);
		break;
	case dungeon:
		rooms = BspMapGen::make_dung_map_ret_rooms(field, MAX_LEVEL);
		break;
	}
}

void Level::place_stairsDown_random()
{
	static int x = 0, y = 0;
	do
	{
		x = random(3, MYLENGTH - 3);
		y = random(3, MYHEIGHT - 3);
	} while ((levelType == cave && field[y][x]->get_isObstacle()) ||
			(levelType == dungeon && !field[y][x]->get_isInRoom()));
	
	field[y][x]->set_stairsDown(true);
	field[y][x]->set_changedPrint(true);
	stairsDown = field[y][x];
}

void Level::set_true_all_changedPrint()
{
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
			field[i][j]->set_changedPrint(true);
}

void Level::RESET_field()
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place> x : field[i])
		{
			x->RESET();
		}
	}

	stairsDown->set_stairsDown(false);
}



std::vector<SharedPtr<CharacterEnemy>> Level::fill_with_monsters()
{
	switch (levelType)
	{
	case (dungeon):
	{

	}


	}

	   
}