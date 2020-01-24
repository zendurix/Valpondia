#pragma once

#include "Character.h"
#include "Place.h"
#include "PathFinding.h"
#include "general_purpose_func.h"


enum ENattitude { hostile = 0, neutral, friendly };
enum ENstate { sleeping = 0, watching, angry };

class CharacterEnemy : public Character
{
private:
	ENattitude attitude;
	ENstate state;


public:
	CharacterEnemy(short x, short y, std::vector<std::vector<std::shared_ptr<Place> >> *field);
	~CharacterEnemy();
	
	void choose_what_to_do();
	void follow_target_Astar(std::shared_ptr<Place> target);
	void follow_target_shortest_way(std::shared_ptr<Place> target);
	void calcullate_distances_for_following(double* distanceArr, std::shared_ptr<Place> target);
};

