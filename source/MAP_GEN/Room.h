#pragma once

#include "Place.h"

class Place;
class Character;


class Room
{
public:
	struct Corner
	{
		int x;
		int y;
		SharedPtr<Place> cornerPtr;
	};

	Corner cornerNW; //1			   1---------------2
	Corner cornerNE; //2    		   |    ROOM       |
	Corner cornerSW; //3			   |    inside     |
	Corner cornerSE; //4			   3---------------4

	int height;
	int length;

	int roomIndex;

	std::vector <SharedPtr<Place> > inRoom;
	std::vector <SharedPtr<Place> > walls;

	Room();
	~Room();

	void make_corner(SharedPtr<Place> field, int cornerNum);
	void calculate_sizes();
};

