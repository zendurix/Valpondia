#pragma once

//random cave generator, based on Cellular Automata algorithm


#include "CONFIGURATION.h"
#include "Place.h"
#include "RNG.h"
#include "GAME.h" 


// parameters for Cellular Automata
const int ALIVE_CHANCE_PERCENT = 45;
const int STEP_LIMIT = 8;
const int DEATH_LIMIT = 3;
const int BIRTH_LIMIT = 4;
const int MIN_CAVE_SIZE_PERCENT = 50;

typedef struct CA_Place
{
	bool isAlive = false;   // !isAlive == isObstacle , isAlive == floor
	bool isAliveNext = false;
	bool chcecked = false;
	int caveIndex = 0;
	int x = -1;
	int y = -1;
}CA_Place;

class CA_cave_gen
{
private:
	CA_Place CA_field[MYHEIGHT][MYLENGTH];

public:
	CA_cave_gen(bool testing, std::vector<std::vector<SharedPtr<Place> >> &fieldArr);
	~CA_cave_gen();

	void set_random_state();
	void make_step();
	void update_state();
	int count_neighbours(int y, int x);
	void set_map(std::vector<std::vector<SharedPtr<Place> >> &fieldArr);
	bool delete_small_caves();
	int count_surface(int y, int x, int index);
	CA_Place* next_in_cave(int y, int x);
	void reset_CA_field();
};


