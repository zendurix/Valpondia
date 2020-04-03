#pragma once
//random cave generator, based on Cellular Automata algorithm

#include "CONFIGURATION.h"


class Place;


struct CA_Place
{
	bool isAlive = false;   // !isAlive == isObstacle , isAlive == floor
	bool isAliveNext = false;
	bool chcecked = false;
	int caveIndex = 0;
	int x = -1;
	int y = -1;
};


class CAMapGen
{
public:

	static void make_cave_map(Vector2D<SharedPtr<Place>>& field, bool testing = false);

private:
	// parameters for Cellular Automata
	const int ALIVE_CHANCE_PERCENT = 45;
	const int STEP_LIMIT = 8;
	const int DEATH_LIMIT = 3;
	const int BIRTH_LIMIT = 4;
	const int MIN_CAVE_SIZE_PERCENT = 50;

	CA_Place CA_field[MYHEIGHT][MYLENGTH];


	CAMapGen(Vector2D<SharedPtr<Place>>& fieldArr, bool testing);
	~CAMapGen();

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


