#include "pch.h"
#include "Level.h"

#include "Place.h"
#include "GAME.h"
#include "RNG.h"
#include "MAP_GEN/map_functions.h"
#include "MAP_GEN/BSPMapGen.h"
#include "MAP_GEN/CAMapGen.h"
#include "MAP_GEN/BasementMapGen.h"


Level::Level(LvType lvType, int depthLevel, SharedPtr<Place>  stairsDown, std::string fileName,
	std::vector<SharedPtr<Room>>* previousRooms)
	: mapFileName(fileName), depth(depthLevel),levelType(lvType), prevStairsDown(stairsDown), prevRooms(previousRooms)
{
	levelCount++;
	levelID = levelCount;
	init_field();
	make_level();
}

Level::~Level() {}

void Level::RESET_field()
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place> x : field[i])
		{
			x->RESET();
		}
	}
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
			fieldRow.push_back(std::make_shared<Place>(levelID));
		}
		field.push_back(fieldRow);
	}
}













void Level::make_level()
{
	switch (levelType)
	{
	case LvType::ruins:
		{
			make_map_ruins(*this);
			break;
		}
	case LvType::cave:
		{	
			do
			{
				CAMapGen::make_cave_map(field);
			} while (!is_place_for_stairsUp());
			break;
		}
	case LvType::dungeon:
		{	do
			{
				rooms = BspMapGen::make_dung_map_ret_rooms(*this, MAX_LEVEL);
			} while (!is_place_for_stairsUp());
			break;
		}
	case LvType::fromFile:
		{
			load_map_from_file(*this, mapFileName);
			break;
		}
	case LvType::basements:
		{
			BasementMapGen::make_basement_map(*this, *prevRooms);
		}
	} 		
	if (prevStairsDown != nullptr)
		stairsUp = field[prevStairsDown->get_y()][prevStairsDown->get_x()];
}







bool Level::is_place_for_stairsUp()
{
	if (levelType == LvType::cave)
	{
		if (field[prevStairsDown->get_y()][prevStairsDown->get_x()]->get_isObstacle())
			return false;
		else
			return true;
	}
	else if (levelType == LvType::dungeon)
	{
		if (field[prevStairsDown->get_y()][prevStairsDown->get_x()]->is_in_room() && 
			!field[prevStairsDown->get_y()][prevStairsDown->get_x()]->get_isObstacle())
			return true;
		else
			return false;
	}
}




void Level::place_stairsDown_random()  // MDELETE
{
//static int x = 0, y = 0;
//do
//{
//	x = RNG::randInt(3, MYLENGTH - 3);
//	y = RNG::randInt(3, MYHEIGHT - 3);
//} while ((levelType == cave && field[y][x]->get_isObstacle()) ||
//	(levelType == dungeon && !field[y][x]->get_isInRoom()));
//
//field[y][x]->set_stairsDown(true);
//field[y][x]->set_changedPrint(true);
//stairsDown = field[y][x];
}









// std::vector<SharedPtr<CharacterEnemy>> Level::fill_with_monsters()
// {
// 	switch (LvType)
// 	{
// 	case LvType::dungeon:
// 	{
// 
// 	}
// 
// 
// 	}
// 
// 
// }