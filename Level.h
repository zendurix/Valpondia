#pragma once

#include "CONFIGURATION.h"
#include "ECS/ECS_Coordinator.h"


class Place;
class Room;

class Level
{
	friend class GAME;
private:
	inline static int levelCount = -1;

	LvType  levelType;
	int depth;
	int levelID;

	std::string mapFileName;
	std::vector <SharedPtr<Room>> rooms;
	std::vector <SharedPtr<Room>>* prevRooms;


	std::vector<Entity> charactersOnLevel;

	SharedPtr<Place> prevStairsDown;
	SharedPtr<Place> stairsUp;
	SharedPtr<Place> stairsDown;

	Vector2D<SharedPtr<Place>> field; //vector equivalent of  Place field[MYHEIGHT][MYLENGTH];


	std::vector<Entity> entitiesToUpdate;


	void init_field();
	void make_level();

public:
	Level(LvType p_levelType, int depthLevel, SharedPtr<Place> stairsDown, std::string fileName = "", 
		std::vector<SharedPtr<Room>>* previousRooms = nullptr);
	~Level();

	bool is_place_for_stairsUp();
	//void change_levelType(LvType levelType);
	void place_stairsDown_random();

	void RESET_field();



	// getters:
	inline static int get_LevelCount()						{ return levelCount; };
	inline Vector2D<SharedPtr<Place>>& get_fieldRef()		{ return field; }
	inline std::vector<Entity>& get_charactersOnLevelRef()  { return charactersOnLevel; }
	inline std::vector<SharedPtr<Room>>& get_roomsRef()		{ return rooms; }

	inline int getDepth()						const { return depth; };
	inline SharedPtr<Place>  get_stairsDown()	const { return stairsDown; };
	inline SharedPtr<Place>  get_stairsUp()		const { return stairsUp; };


	// setters
	inline void set_stairsDown(SharedPtr<Place> set)	{ stairsDown = set; };
	inline void set_stairsUp(SharedPtr<Place> set)		{ stairsUp = set; };
	inline void set_rooms(std::vector<SharedPtr<Room>> roomsVec) { rooms = roomsVec; }


};

