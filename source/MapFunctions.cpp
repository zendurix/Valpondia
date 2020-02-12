#include "pch.h"
#include "MapFunctions.h"


void make_map_ruins(Level& level)
{
	int ruinsNumb = random(RUINS_MIN, RUIN_MAX);
	int x, y, length, height;
	std::vector<SharedPtr<Room>> ruins;
	SharedPtr<Room> ruin;

	load_map_from_file(level, "valpondia_ruins.txt");

	std::vector<SharedPtr<Place>> excludedZone = { level.field[15][35], level.field[15][68], level.field[37][35], level.field[37][68] };
	std::vector<SharedPtr<Place>> excludedZone2 = { level.field[18][0], level.field[18][35], level.field[34][35], level.field[34][0] };


	for (int i = 0; i < ruinsNumb; i++)
	{
		ruin = std::make_shared<Room>();
		bool overlapZone = true;
		bool overlapZone2 = true;
		bool overlapRoom = true;
		do
		{
			length = random(5, 15);
			height = random(5, 13);
			x = random(2, (MYLENGTH - 4) - length);
			y = random(2, (MYHEIGHT - 4) - height);
			std::vector<SharedPtr<Place>> ruinZone = { level.field[y][x], level.field[y][x + length],	level.field[y + height][x + length], level.field[y + height][x] };
			overlapZone = zonesOverlaps(excludedZone, ruinZone);
			overlapZone2 = zonesOverlaps(excludedZone2, ruinZone);
			overlapRoom = overlapOtherRoom(level.field, ruinZone);
		} while (overlapRoom || overlapZone || overlapZone2);
		make_room(level.field, x, y, length, height, ruin, true);
		ruins.push_back(ruin);

	}
	SharedPtr<Room> ruinWithBasement = random_from_vect(ruins);
	SharedPtr<Place> stairsToBasement = random_from_vect(ruinWithBasement->inRoom);
	stairsToBasement->set_stairsDown(true);
	level.set_stairsDown(stairsToBasement);
}


void make_room(Vector2D<SharedPtr<Place>>& field, int x, int y, int length1, int length2, SharedPtr <Room> room, bool ruin)
{
	int startX = x,
		startY = y;

	/*1*/auto make_upper_wall = [&]()
	{
		x = startX;
		y = startY;
		for (int i = 0; i < length1 + PLACE_FOR_WALLS / 2; i++)
		{
			field[y][x]->make_wall();
			field[y][x]->set_printFormat(179);
			field[y][x]->set_prevPrintFormat(179);
			room->walls.push_back(field[y][x]);
			field[y][x]->set_roomHere(room);

			if (i == 0)									room->make_corner(field[y][x], 1);
			if (i == (length1 + PLACE_FOR_WALLS / 2)-1) room->make_corner(field[y][x], 2);
			x++;
		}
	};
	/*2*/auto make_down_wall = [&]()
	{
		x = startX;
		y = startY + length2 + PLACE_FOR_WALLS / 2;
		for (int i = 0; i < length1 + PLACE_FOR_WALLS / 2; i++)
		{
			field[y][x]->make_wall();
			field[y][x]->set_printFormat(179);
			field[y][x]->set_prevPrintFormat(179);
			room->walls.push_back(field[y][x]);
			field[y][x]->set_roomHere(room);
			if (i == 0)									  room->make_corner(field[y][x], 3);
			if (i == (length1 + PLACE_FOR_WALLS / 2) - 1) room->make_corner(field[y][x], 4);
			x++;
		}
	};
	/*3*/auto make_left_wall = [&]()
	{
		x = startX;
		y = startY + PLACE_FOR_WALLS / 2;
		for (int i = 0; i < length2; i++)
		{
			field[y][x]->make_wall();
			field[y][x]->set_printFormat(179);
			field[y][x]->set_prevPrintFormat(179);
			room->walls.push_back(field[y][x]);
			field[y][x]->set_roomHere(room);
			y++;
		}
	};
	/*4*/auto make_right_wall = [&]()
	{
		x = startX + length1;
		y = startY + PLACE_FOR_WALLS / 2;
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
	};
	
	auto make_room_inside = [&](bool makeFloors)
	{
		x = startX + 1;
		y = startY + 1;
		for (int i = 0; i < length2; i++)
		{
			for (int j = 0; j < length1 - 1; j++)
			{
				if (makeFloors)
				{
					field[y][x]->unmake_obstacle();
				}
				field[y][x]->set_isInRoom(true);
				field[y][x]->set_roomHere(room);
				room->inRoom.push_back(field[y][x]);
				x++;
			}
			x = startX + 1;
			y++;
		}
	};

	if (room == nullptr)
	{
		SharedPtr <Room> room1 = std::make_shared <Room>();
		room = room1;
	}

	if (!ruin)
	{
		make_upper_wall();
		make_down_wall();
		make_left_wall();
		make_right_wall();
		make_room_inside(true);
	}
	else if (ruin)
	{
		int missingWalls = random(0, 2);
		int missingWallsID[2] = { -1, -1 };
		if (missingWalls != 0)
		{
			missingWallsID[0] = random(1, 4);
			if (missingWalls == 2)
			{
				missingWallsID[1] = (missingWallsID[0] == 1) ? random(3, 4) :
					(missingWallsID[0] == 2) ? random(3, 4) :
					(missingWallsID[0] == 3) ? random(1, 2) :
					(missingWallsID[0] == 4) ? random(1, 2) : 1;
			}
		}


		for (int i = 1; i <= 4; i++)
		{
			if (missingWallsID[0] != i && missingWallsID[1] != i)
			{
				switch (i)
				{
				case 1:	make_upper_wall();	break;
				case 2:	make_down_wall();	break;
				case 3:	make_left_wall();	break;
				case 4:	make_right_wall();	break;
				}
			}
		}
		make_room_inside(false);


		int holesInWall = random(2, room->walls.size()/2);
		for (int i = 0; i < holesInWall; i++)
		{
			SharedPtr<Place> makeHole = random_from_vect(room->walls);
			//vector_pop(room->walls, makeHole);
			makeHole->unmake_obstacle();
		}

	}




	room->calculate_sizes();	
}



void make_whole_map_obstacle(Vector2D<SharedPtr<Place>>& field)
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place>  x : field[i])
		{
			x->make_obstacle();
		}
	}
}


void make_whole_map_not_obstacle(Vector2D<SharedPtr<Place>>& field)
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place> x : field[i])
		{
			x->unmake_obstacle();
		}
	}
}



void load_map_from_file(Level& level, std::string fileName)
{
	std::string path = "../res/maps/" + fileName;
	std::string line;
	int i = 0;

	std::ifstream file;
	file.open(path);
	while (getline(file, line))
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			switch (line[j])
			{
			case '.':
				level.field[i][j]->unmake_obstacle();
				break;
			case '#':
				level.field[i][j]->make_obstacle();
				break;

			case '>':
				level.field[i][j]->unmake_obstacle();
				level.field[i][j]->set_stairsDown(true);
				level.set_stairsDown(level.field[i][j]);
				break;

			case '<':
				level.field[i][j]->unmake_obstacle();
				level.field[i][j]->set_stairsUp(true);
				level.set_stairsUp(level.field[i][j]);
				break;
			}
		}
		i++;
	}
}



bool zonesOverlaps(std::vector<SharedPtr<Place>> zone1, std::vector<SharedPtr<Place>> zone2)
{
	int x1a = zone1[0]->get_x();
	int	y1a = zone1[0]->get_y();
	int x1b = zone1[1]->get_x();
	int	y1b = zone1[1]->get_y();
	int x1c = zone1[2]->get_x();
	int	y1c = zone1[2]->get_y();
	int x1d = zone1[3]->get_x();
	int	y1d = zone1[3]->get_y();

	for (int i = 0; i <= 3; i++)
	{
		int x = zone2[i]->get_x(),	 y = zone2[i]->get_y();

		if ((x >= x1a && x <= x1b) && (y >= y1a && y <= y1c))
		{
			return true;
		}
	}
	return false;
}

bool overlapOtherRoom(Vector2D<SharedPtr<Place>>& field, std::vector<SharedPtr<Place>> zone)
{
	for (int i = zone[0]->get_x(); i <= zone[1]->get_x(); i++)
		for (int j = zone[0]->get_y(); j <= zone[3]->get_y(); j++)
			if (field[j][i]->get_isInRoom())
				return true;
	return false;
}