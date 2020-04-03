#include "pch.h"
#include "BasementMapGen.h"

#include "Room.h"
#include "map_functions.h"
#include "../GAME.h"
#include "../Place.h"
#include "../Level.h"
#include "../RNG.h"
#include "../general_purpose_func.h"


const int SCARAB_BASEMENT_CHANCE = 60;


void BasementMapGen::make_basement_map(Level& level, std::vector<SharedPtr<Room>> roomsOnSurface)
{
	BasementMapGen mapGen(level, roomsOnSurface);

	int restartCount = 0;
	bool restart = true;
	while (restart)
	{
		//make_whole_map_obstacle(level.get_fieldRef());
		try
		{
			mapGen.add_basements();
			restart = false;
		}
		catch (const char* error)
		{
			restart = true;
			restartCount++;
			level.RESET_field();
		}
	}
	LOG("Basements restart count: " << restartCount);


	mapGen.add_random_stairsDown();
	mapGen.fill_basements();


}




BasementMapGen::BasementMapGen(Level& level, std::vector<SharedPtr<Room>> roomsOnSurface)
	: levelRef(level), roomsOnSurface(roomsOnSurface)
{
}

BasementMapGen::~BasementMapGen()
{}





void BasementMapGen::add_basements()
{
	const int BASEMENT_WITH_STAIRSUP_CHANCE = 100;

	SharedPtr<Room> basement;

	for (SharedPtr<Room> room : roomsOnSurface)
	{
		if (room->stairsDownHere != nullptr)
		{
			basement = make_basement(room);

			add_stairsUp(*basement, room->stairsDownHere->get_connector());

			basements.push_back(basement);
		}
	}

	// delete walls inside, if two or more basements overlaps
	for (SharedPtr<Room> basement : basements)
	{
		for (SharedPtr<Place> inside : basement->inRoom)
		{
			if (inside->get_isObstacle())
				inside->unmake_obstacle();
		}
	}
}

SharedPtr<Room> BasementMapGen::make_basement(SharedPtr<Room> ruinAbove)
{	
	SharedPtr<Room> basement = std::make_shared<Room>();
	int minLentgh, maxLength, length, minHeight, maxHeight, height, xMin, xMax, x, yMin, yMax, y;
	int restart_count = 0;

	do	
	{
		minLentgh = ruinAbove->length / 2;
		maxLength = ruinAbove->length + 4;
		length = RNG::randInt(minLentgh, maxLength);

		minHeight = ruinAbove->height / 2;
		maxHeight = ruinAbove->height + 4;
		height = RNG::randInt(minHeight, maxHeight);

		xMin = ruinAbove->stairsDownHere->get_x() - length - 2;
		xMax = ruinAbove->stairsDownHere->get_x() - 2;
		x = RNG::randInt(xMin, xMax); 
		x = (x <= 0) ? 1 : x;

		yMin = ruinAbove->stairsDownHere->get_y() - height - 2;
		yMax = ruinAbove->stairsDownHere->get_y() - 2;
		y = RNG::randInt(yMin, yMax);
		y = (y <= 0) ? 1 : y;

		restart_count++;
		if (restart_count > 400)
			throw "Stuck in loop Error";


	} while (x >= ruinAbove->stairsDownHere->get_x() || y >= ruinAbove->stairsDownHere->get_y() ||
			x + length <= ruinAbove->stairsDownHere->get_x() || y + height <= ruinAbove->stairsDownHere->get_y() || 
			x <= 0 || y <= 0 || x + length + PLACE_FOR_WALLS >= MYLENGTH - 1 ||	
			y + height + PLACE_FOR_WALLS >= MYHEIGHT - 1);

	make_room(levelRef.get_fieldRef(), x, y, length, height, basement);

	return basement;
}

void BasementMapGen::add_stairsUp(Room& basement, const Connector& stairsDown)
{
	Connector stairsUp{ stairsDown.destinationY, stairsDown.destinationX, stairsDown.destinationLevel - 2, '+', false, true }; // MCHANGE

	for (SharedPtr<Place> place : basement.inRoom)
	{
		if (place->get_x() == stairsDown.destinationX && place->get_y() == stairsDown.destinationY)
		{
			place->set_connector(stairsUp);
			basement.stairsUpHere = place;
			break;
		}
	}
}



void BasementMapGen::add_random_stairsDown()
{
	SharedPtr<Room> basementWithStairsDown = RNG::random_from_vect(basements);
	SharedPtr<Place> stairsDown;
	do
	{
		stairsDown = RNG::random_from_vect(basementWithStairsDown->inRoom);
	} while (stairsDown->get_connector() != Place::NULLConnector);

	Connector stairs{ stairsDown->get_y(), stairsDown->get_x(), 3, '-', true, false };
	stairsDown->set_connector(stairs);
	basementWithStairsDown->stairsDownHere = stairsDown;

	levelRef.set_stairsDown(stairsDown);
}





void BasementMapGen::fill_basements()
{
	add_scarabs();

}


void BasementMapGen::add_scarabs()
{
	for (auto basement : basements)
	{
		if (RNG::randInt(0, 100) <= SCARAB_BASEMENT_CHANCE)
			make_scarab_hive_in_basement(basement);
	}
}

void BasementMapGen::make_scarab_hive_in_basement(SharedPtr<Room> ruin)
{
	std::vector<SharedPtr<Place>> inside = ruin->inRoom;

	int maxScarabs = 8;
	int minScarabs = 1;
	int scarabsNum = RNG::randInt(minScarabs, maxScarabs);


	for (int i = 0; i < scarabsNum; i++)
	{
		SharedPtr<Place> place = RNG::random_from_vect(inside);
		vector_pop(inside, place);
		gamePtr->Factory->make_junkScarab(place);
	}

}

