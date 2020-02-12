#pragma once

#include "Character.h"
#include "Place.h"
#include "PathFinding.h"
#include "general_purpose_func.h"


enum ENattitude { hostile = 0, neutral, friendly };
enum ENstate { sleeping = 0, watching, angry };

enum EnemyType {rat= 0 , };

class CharacterEnemy : public Character
{
private:
	ENattitude attitude;
	ENstate state;


public:

	static SharedPtr<CharacterEnemy> make_enemy(EnemyType type, short x, short y, std::vector<std::vector<SharedPtr<Place> >> *field);


	CharacterEnemy(short x, short y, std::vector<std::vector<SharedPtr<Place> >> *field);
	~CharacterEnemy();
	
	void choose_what_to_do();
	void follow_target_Astar(SharedPtr<Place> target);
	void follow_target_shortest_way(SharedPtr<Place> target);
	void calcullate_distances_for_following(double* distanceArr, SharedPtr<Place> target);
};

