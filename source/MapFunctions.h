#pragma once

#include "CA_cave_gen.h"
#include "BSPMapGen.h"
#include "Room.h"
#include "GAME.h"
#include "general_purpose_func.h"



void make_cave_map(bool testing, std::vector<std::vector<std::shared_ptr<Place> >> &fieldArr);

std::vector <std::shared_ptr <Room>> make_dung_map_ret_rooms(bool test);

void make_room(std::string shape_name, int x, int y, int length1, int length2,
	std::shared_ptr <Room> room, std::string orientation = "horizontal", bool bspRoom = false);

void make_whole_map_obstacle();
void make_whole_map_not_obstacle();



