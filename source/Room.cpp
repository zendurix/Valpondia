#include "pch.h"
#include "Room.h"


Room::Room()
{
}


Room::~Room() 
{
	inRoom.clear();
	walls.clear();
}

void Room::make_corner(SharedPtr<Place> field, int cornerNum)
{
	switch (cornerNum)
	{
	case 1:
		cornerNW.cornerPtr = field;
		cornerNW.x = field->get_x();
		cornerNW.y = field->get_y();
		break;
	case 2:
		cornerNE.cornerPtr = field;
		cornerNE.x = field->get_x();
		cornerNE.y = field->get_y();
		break;
	case 3:
		cornerSW.cornerPtr = field;
		cornerSW.x = field->get_x();
		cornerSW.y = field->get_y();
		break;
	case 4:
		cornerSE.cornerPtr = field;
		cornerSE.x = field->get_x();
		cornerSE.y = field->get_y();
		break;
	}
}

void Room::calculate_sizes()
{
	height = cornerSE.y - cornerNE.y;
	length = cornerNE.x - cornerNW.x;
}
