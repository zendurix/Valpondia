#pragma once

#include "CONFIGURATION.h"
#include "Place.h"
#include "GAME.h"
#include "BSPMapGen.h"
#include "CA_cave_gen.h"



class Level
{
	friend class GAME;
	friend class GAME_charControler;

private:
	inline static int levelCount = -1;
	lvType  levelType;
	int depth;
	int levelID;
	std::string mapFileName;

	SharedPtr<Place>  stairsUp;
	SharedPtr<Place>  stairsDown;
	SharedPtr<Place>  prevStairsDown;
	std::vector <SharedPtr<Room>> rooms;

	void init_field();
	void make_level();

public:
	Vector2D<SharedPtr<Place>> field; //vector equivalent of  Place field[MYHEIGHT][MYLENGTH];

	Level(lvType p_levelType, int depthLevel, SharedPtr<Place>  stairsDownm, std::string fileName = "");
	~Level();

	bool isPlaceForStairsUp();
	void changeLevelType(lvType levelType);
	void place_stairsDown_random();
	void set_true_all_changedPrint();
	void RESET_field();

	std::vector<SharedPtr<CharacterEnemy>> fill_with_monsters();


// getters:
	int getDepth()						const  { return depth; };
	SharedPtr<Place>  get_stairsDown()	const  { return stairsDown; };
	SharedPtr<Place>  get_stairsUp()	const  { return stairsUp; };
	static int getLevelCount()			 { return levelCount; };

// setters
	void  set_stairsDown(SharedPtr<Place> set)	{ stairsDown = set; };
	void  set_stairsUp(SharedPtr<Place> set)	{ stairsUp = set; };


};

