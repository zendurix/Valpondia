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

	std::shared_ptr<Place>  stairsUp;
	std::shared_ptr<Place>  stairsDown;
	std::shared_ptr<Place>  prevStairsDown;
	std::vector <std::shared_ptr <Room>> rooms;

	void init_field();
	void make_level();

public:
	std::vector <std::vector <std::shared_ptr<Place> > > field; //vector equivalent of  Place field[MYHEIGHT][MYLENGTH];

	Level(lvType p_levelType, int depthLevel, std::shared_ptr<Place>  stairsDown);
	~Level();

	bool isPlaceForStairsUp();
	void changeLevelType(lvType levelType);
	void place_stairsDown_random();
	void set_true_all_changedPrint();
	void RESET_field();

// getters:
	int getDepth();
	std::shared_ptr<Place>  get_stairsDown();
	std::shared_ptr<Place>  get_stairsUp();
	static int getLevelCount();
};

