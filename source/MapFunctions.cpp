#include "pch.h"
#include "MapFunctions.h"


void make_cave_map(bool testing, std::vector<std::vector<SharedPtr<Place> >> &fieldArr)
{
	CA_cave_gen cave(testing, fieldArr);
}

/*
std::vector<SharedPtr<Room>> make_dung_map_ret_rooms(bool test)
{
	GAME* game = GAME::getInstance();
	std::vector <SharedPtr <Room>> rooms;

	BspMapGen tree(test);

	int restart_count = 0;
	bool restart = false;
	while (!restart)
	{
		try
		{
			tree.make_full_tree();
			restart = true;
		}
		catch (...)
		{
			restart = false;
			restart_count++;
			for (int i = 0; i < MYHEIGHT; i++)
				for (int j = 0; j < MYLENGTH; j++)
					game->levelActive->field[i][j]->RESET();
		}
	}

	LOG("BSP tree restart count: " << restart_count);

	tree.fill_leaves_with_rooms(&rooms);
	tree.connect_all_rooms();

	if (test)
	{
		for (int i = 0; i < MYHEIGHT; i++)
			for (int j = 0; j < MYLENGTH; j++)
				game->levelActive->field[i][j]->set_tileColor(sf::Color::White);
	}
	tree.~tree();
	return rooms;
}
*/


void make_room(std::string shape_name, int x, int y, int length1, int length2, SharedPtr <Room> room)
{
	int startX = x,
		startY = y;
	GAME* game = GAME::getInstance();
	std::vector <std::vector <SharedPtr<Place> > > &field = game->levelActive->field;

	if (room == nullptr)
	{
		SharedPtr <Room> room1 = std::make_shared <Room>();
		room = room1;
	}
	   
	/*
	if (shape_name == "line")
	{
		for (int i = 0; i < length1; i++)
		{
			field[y][x]->unmake_obstacle();
			if (orientation == "horizontal")
				x++;
			else //vertical
				y++;
		}
	}
	*/

	// upper wall
	for (int i = 0; i < length1; i++)
	{
		field[y][x]->make_wall();
		field[y][x]->set_printFormat(196);
		field[y][x]->set_prevPrintFormat(196);
		room->walls.push_back(field[y][x]);
		if (i == 0)
		{
			field[y][x]->set_printFormat(218);
			field[y][x]->set_prevPrintFormat(218);
			room->make_corner(field[y][x], 1);
		}
		if (i == length1 - 1)
		{
			field[y][x]->set_printFormat(191);
			field[y][x]->set_prevPrintFormat(191);
			room->make_corner(field[y][x], 2);
		}
		field[y][x]->set_roomHere(room);
		x++;
	}
	y = startY + length2;
	x = startX;	

	// down wall
	for (int i = 0; i < length1; i++)
	{
		field[y][x]->make_wall();
		field[y][x]->set_printFormat(196);
		field[y][x]->set_prevPrintFormat(196);
		room->walls.push_back(field[y][x]);
		if (i == 0)
		{
			field[y][x]->set_printFormat(192);
			field[y][x]->set_prevPrintFormat(192);
			room->make_corner(field[y][x], 3);
		}
		if (i == length1 - 1)
		{
			field[y][x]->set_printFormat(217);
			field[y][x]->set_prevPrintFormat(217);
			room->make_corner(field[y][x], 4);
		}
		field[y][x]->set_roomHere(room);
		x++;
	}
	x = startX;
	y = startY;

	// left wall
	for (int i = 0; i < length2; i++)
	{
		field[y][x]->make_wall();
		field[y][x]->set_printFormat(179);
		field[y][x]->set_prevPrintFormat(179);
		room->walls.push_back(field[y][x]);
		field[y][x]->set_roomHere(room);
		y++;
	}
	x = startX + length1;
	y = startY;

	//right wall
	for (int i = 0; i < length2; i++)
	{
		field[y][x]->make_wall();
		field[y][x]->set_printFormat(179);
		field[y][x]->set_prevPrintFormat(179);
		room->walls.push_back(field[y][x]);
		field[y][x]->set_roomHere(room);
		y++;
	}
	x = startX + 1;
	y = startY + 1;

	// MAKE ROOM INSIDE
	for (int i = 0; i < length2; i++)
	{
		for (int j = 0; j < length1 - 1; j++)
		{
			field[y][x]->unmake_obstacle();
			field[y][x]->set_isInRoom(true);
			field[y][x]->set_roomHere(room);
			x++;
		}
		x = startX + 1;
		y++;
	}
	room->calculate_sizes();

	
}



void make_whole_map_obstacle()
{
	GAME* game = GAME::getInstance();
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place>  x : game->levelActive->field[i])
		{
			x->make_obstacle();
		}
	}
}


void make_whole_map_not_obstacle()
{
	GAME* game = GAME::getInstance();
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place> x : game->levelActive->field[i])
		{
			x->unmake_obstacle();
		}
	}
}