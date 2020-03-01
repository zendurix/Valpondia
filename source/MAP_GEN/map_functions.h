#pragma once

#include "Room.h"
#include "../general_purpose_func.h"
#include "../Level.h"

#include "../RNG.h"


class Level; // MDELETE
class Room;


void make_room(Vector2D<SharedPtr<Place>>& field, int x, int y, int length1, int length2, SharedPtr <Room> room, bool ruin = false);

void make_whole_map_obstacle(Vector2D<SharedPtr<Place>>& field);
void make_whole_map_not_obstacle(Vector2D<SharedPtr<Place>>& field);


void load_map_from_file(Level& level, const std::string fileName);


void make_map_ruins(Level& level);



bool zones_overlap(const std::vector<SharedPtr<Place>>& zone1, const std::vector<SharedPtr<Place>>& zone2);
bool overlap_other_room(const Vector2D<SharedPtr<Place>>& field, const std::vector<SharedPtr<Place>>& zone);