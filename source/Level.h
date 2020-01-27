#pragma once

#include "CONFIGURATION.h"
#include "Place.h"
#include "GAME.h"
#include "Room.h"
#include "MapFunctions.h"

enum lvType { cave = 0, dungeon };

class Level
{
	friend class GAME;
	friend class GAME_charControler;

private:
	static int levelCount;
	lvType  levelType;
	int depth;
	int levelID;

	SharedPtr<Place>  stairsUp;
	SharedPtr<Place>  stairsDown;
	SharedPtr<Place>  prevStairsDown;
	std::vector <SharedPtr <Room>> rooms;

	void init_field();
	void make_level();

public:
	std::vector <std::vector <SharedPtr<Place> > > field; //vector equivalent of  Place field[MYHEIGHT][MYLENGTH];

	Level(lvType p_levelType, int depthLevel, SharedPtr<Place>  stairsDown);
	~Level();

	bool isPlaceForStairsUp();
	void changeLevelType(lvType levelType);
	void place_stairsDown_random();
	void set_true_all_changedPrint();
	void RESET_field();

// getters:
	int getDepth();
	SharedPtr<Place>  get_stairsDown();
	SharedPtr<Place>  get_stairsUp();
	static int getLevelCount();
};

