#pragma once

#include "../CONFIGURATION.h"
#include "MapGen.h"

class Level;
class Place;
class Room;
class Connector;


class BasementMapGen : public MapGen
{

private:

	inline static LvType ID = LvType::basements;

	Level& levelRef;
	std::vector<SharedPtr<Room>> roomsOnSurface;
	std::vector<SharedPtr<Room>> basements;



	BasementMapGen(Level& level, std::vector<SharedPtr<Room>> roomsOnSurface);
	~BasementMapGen();

	void add_basements();
	SharedPtr<Room> make_basement(SharedPtr<Room> ruinAbove);
	void add_stairsUp(Room& basement, const Connector& stairsDown);

	void make_scarab_hive_in_basement(SharedPtr<Room> ruin);
	void fill_basements();
	void add_scarabs();
	void add_random_stairsDown();

public:

	static void make_basement_map(Level& level, std::vector<SharedPtr<Room>> roomsOnSurface);


};

