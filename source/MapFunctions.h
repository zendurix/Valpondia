#pragma once

#include "Room.h"
#include "GAME.h"
#include "general_purpose_func.h"
#include "Level.h"

class Level;


void make_room(Vector2D<SharedPtr<Place>>& field, int x, int y, int length1, int length2, SharedPtr <Room> room, bool ruin = false);

void make_whole_map_obstacle(Vector2D<SharedPtr<Place>>& field);
void make_whole_map_not_obstacle(Vector2D<SharedPtr<Place>>& field);


void load_map_from_file(Level& level, std::string fileName);


void make_map_ruins(Level& level);



bool zonesOverlaps(std::vector<SharedPtr<Place>> zone1, std::vector<SharedPtr<Place>> zone2);
bool overlapOtherRoom(Vector2D<SharedPtr<Place>>& field, std::vector<SharedPtr<Place>> zone);