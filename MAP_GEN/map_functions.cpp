#include "pch.h"
#include "map_functions.h"

#include "Room.h"
#include "../general_purpose_func.h"
#include "../Level.h"
#include "../RNG.h"


void make_map_ruins(Level& level)
{
	Vector2D<SharedPtr<Place>>& field = level.get_fieldRef();
	int ruinsNumb = RNG::randInt(RUINS_MIN, RUINS_MAX);
	int x, y, length, height;
	std::vector<SharedPtr<Room>> ruins;
	SharedPtr<Room> ruin;

	std::vector<SharedPtr<Place>> excludedZone  = { field[15][35], field[15][68], field[37][35], field[37][68] };
	std::vector<SharedPtr<Place>> excludedZone2 = { field[18][0], field[18][35], field[34][35], field[34][0] };

	const int BASEMENT_CHANCE = 75;
	const int STAIRS_TO_BASEMENT_CHANCE = 60;

	bool restart = true;
	int restart_count = 0;


	while (restart)
	{
		load_map_from_file(level, "valpondia_ruins.txt");
		restart = false;
		ruins.clear();

		for (int i = 0; i < ruinsNumb; i++)
		{
			ruin = std::make_shared<Room>();
			bool overlapZone = true;
			bool overlapZone2 = true;
			bool overlapRoom = true;

			do
			{
				length = RNG::randInt(5, 15);
				height = RNG::randInt(5, 13);
				x = RNG::randInt(2, (MYLENGTH - 4) - length);
				y = RNG::randInt(2, (MYHEIGHT - 4) - height);
				std::vector<SharedPtr<Place>> ruinZone = { field[y][x], field[y][x + length], field[y + height][x + length], field[y + height][x] };
				overlapZone = zones_overlap(excludedZone, ruinZone);
				overlapZone2 = zones_overlap(excludedZone2, ruinZone);
				overlapRoom = overlap_other_room(field, ruinZone);

				restart_count++;
				if (restart_count > 600)
				{
					restart_count = 0;
					restart = true;
					level.RESET_field();
				}

			} while ((overlapRoom || overlapZone || overlapZone2) && !restart);

			if (!restart)
			{
				make_room(field, x, y, length, height, ruin, true);

				if (RNG::randInt(0, 100) <= BASEMENT_CHANCE)
				{
					SharedPtr<Place> stairs;

					do
					{
						stairs = RNG::random_from_vect(ruin->inRoom);
					} while (stairs->get_isObstacle());

					Connector stairsDown{ stairs->get_y(), stairs->get_x(), 2, '-', true };
					stairs->set_connector(stairsDown);
					ruin->stairsDownHere = stairs;
				}

				ruins.push_back(ruin);
			}
		}
	}

	LOG("RUINS RESTART COUNT " << restart_count);

	level.set_rooms(ruins);
}


















void make_room(Vector2D<SharedPtr<Place>>& field, int x, int y, int length1, int length2, SharedPtr<Room> room, bool ruin)
{
	int startX = x,
		startY = y;


	/*1*/auto make_upper_wall = [&]()
	{
		x = startX;
		y = startY;
		for (int i = 0; i < length1 + PLACE_FOR_WALLS / 2; i++)
		{
			field[y][x]->make_obstacle(ObstacleType::rock);
			room->walls.push_back(field[y][x]);
			field[y][x]->set_roomHere(room);

			if (i == 0)									  room->make_corner(field[y][x], 1);
			if (i == (length1 + PLACE_FOR_WALLS / 2) - 1) room->make_corner(field[y][x], 2);
			x++;
		}
	};
	/*2*/auto make_down_wall = [&]()
	{
		x = startX;
		y = startY + length2 + PLACE_FOR_WALLS / 2;
		for (int i = 0; i < length1 + PLACE_FOR_WALLS / 2; i++)
		{
			field[y][x]->make_obstacle(ObstacleType::rock);
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
			field[y][x]->make_obstacle(ObstacleType::rock);
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
			field[y][x]->make_obstacle(ObstacleType::rock);
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
		int missingWalls = RNG::randInt(0, 2);
		int missingWallsID[2] = { -1, -1 };
		if (missingWalls != 0)
		{
			missingWallsID[0] = RNG::randInt(1, 4);
			if (missingWalls == 2)
			{
				missingWallsID[1] = (missingWallsID[0] == 1) ? RNG::randInt(3, 4) :
					(missingWallsID[0] == 2) ? RNG::randInt(3, 4) :
					(missingWallsID[0] == 3) ? RNG::randInt(1, 2) :
					(missingWallsID[0] == 4) ? RNG::randInt(1, 2) : 1;
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


		int holesInWall = RNG::randInt(2, room->walls.size() / 2);
		for (int i = 0; i < holesInWall; i++)
		{
			SharedPtr<Place> makeHole = RNG::random_from_vect(room->walls);
			vector_pop(room->walls, makeHole);
			makeHole->unmake_obstacle();
		}
		
	}

	room->height = length2;
	room->length = length1;

	//room->calculate_sizes();
}	













void make_whole_map_obstacle(Vector2D<SharedPtr<Place>>& field)
{
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (SharedPtr<Place> place : field[i])
		{
			place->make_obstacle(ObstacleType::rock);
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
	Vector2D<SharedPtr<Place>>& field = level.get_fieldRef();

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
				field[i][j]->unmake_obstacle();
				break;
			case '#':
				field[i][j]->make_obstacle(ObstacleType::rock);
				break;

			case '>':
				field[i][j]->unmake_obstacle();
				//field[i][j]->set_stairsDown(true);  // MCHANGE
				level.set_stairsDown(field[i][j]);
				break;

			case '<':
				field[i][j]->unmake_obstacle();
				//field[i][j]->set_stairsUp(true);  // MCHANGE
				level.set_stairsUp(field[i][j]);
				break;
			}
		}
		i++;
	}
}



bool zones_overlap(const std::vector<SharedPtr<Place>>& zone1, const std::vector<SharedPtr<Place>>& zone2)
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
		int x = zone2[i]->get_x(), y = zone2[i]->get_y();

		if ((x >= x1a && x <= x1b) && (y >= y1a && y <= y1c))
		{
			return true;
		}
	}
	return false;
}

bool overlap_other_room(const Vector2D<SharedPtr<Place>>& field, const std::vector<SharedPtr<Place>>& zone)
{
	for (int i = zone[0]->get_x(); i <= zone[1]->get_x(); i++)
		for (int j = zone[0]->get_y(); j <= zone[3]->get_y(); j++)
			if (field[j][i]->is_in_room())
				return true;
	return false;
}