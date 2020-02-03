#include "pch.h"
#include "CA_cave_gen.h"


CA_cave_gen::CA_cave_gen(bool testing, std::vector<std::vector<SharedPtr<Place> >> &fieldArr)
{
	GAME *game = GAME::getInstance();
	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			CA_field[i][j].y = i;
			CA_field[i][j].x = j;
		}
	}

	bool repeat = true;
	while (repeat)
	{
		set_random_state();

		for (int i = 0; i <= STEP_LIMIT+1; i++)
		{
			if (testing)
			{
				set_map(fieldArr);
				game->Printer->print_field();
				LOG("CA step: " << i);
				Input::wait_for_input(inputType::space);
			}

			if (i < STEP_LIMIT)
			{
				make_step();
			}

			if (i == STEP_LIMIT)
			{
				repeat = delete_small_caves();
				if (repeat && !testing)
					reset_CA_field();
				else
					repeat = false;
			}
		}
	}

	set_map(fieldArr);
}

CA_cave_gen::~CA_cave_gen()
{
}


void CA_cave_gen::set_random_state()
{
	for (int i = 1; i < MYHEIGHT - 1; i++)
		for (int j = 1; j < MYLENGTH - 1; j++)
		{
			if (random(0, 100) <= ALIVE_CHANCE_PERCENT)
				CA_field[i][j].isAlive = true;
			else
				CA_field[i][j].isAlive = false;
		}
}

void CA_cave_gen::make_step()
{
	int neighbours;
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
		{
			neighbours = count_neighbours(i, j);

			if (CA_field[i][j].isAlive)
			{
				if (neighbours < DEATH_LIMIT)
					CA_field[i][j].isAliveNext = false;
				else
					CA_field[i][j].isAliveNext = true;
			}
			else
			{
				if (neighbours > BIRTH_LIMIT)
					CA_field[i][j].isAliveNext = true;
				else
					CA_field[i][j].isAliveNext = false;
			}
		}

	update_state();
}

void CA_cave_gen::update_state()
{
	for (int i = 1; i < MYHEIGHT - 1; i++)
		for (int j = 1; j < MYLENGTH - 1; j++)
			CA_field[i][j].isAlive = CA_field[i][j].isAliveNext;
}

int CA_cave_gen::count_neighbours(int y, int x)
{
	int count = 0;

	if (x > 1)
	{
		if (CA_field[y][x - 1].isAlive)
			count++;

		if (y > 1)
			if (CA_field[y - 1][x - 1].isAlive)
				count++;
		if (y < (MYHEIGHT - 2))
			if (CA_field[y + 1][x - 1].isAlive)
				count++;
	}

	if (y > 1)
	{
		if (CA_field[y - 1][x].isAlive)
			count++;
		if (x < (MYLENGTH - 2))
			if (CA_field[y - 1][x + 1].isAlive)
				count++;
	}

	if (y < (MYHEIGHT - 2))
		if (CA_field[y + 1][x].isAlive)
			count++;
	if (x < (MYLENGTH - 2))
	{
		if (CA_field[y][x + 1].isAlive)
			count++;
		if (y < (MYHEIGHT - 2))
			if (CA_field[y + 1][x + 1].isAlive)
				count++;
	}

	return count;
}

void CA_cave_gen::set_map(std::vector<std::vector<SharedPtr<Place> >> &fieldArr)
{
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
		{
			if (!CA_field[i][j].isAlive)
				fieldArr[i][j]->make_obstacle();
			else
				fieldArr[i][j]->unmake_obstacle();
			if (j == 0 || j == MYLENGTH - 1 || i == 0 || i == MYHEIGHT - 1) // making frame
				fieldArr[i][j]->make_obstacle();
		}

}

bool CA_cave_gen::delete_small_caves()
{
	int index = 0;
	int maxSurfInd;
	int maxSurf = 0;
	int surfaceByIndex[40];
	for (int i = 1; i < MYHEIGHT - 1; i++)
		for (int j = 1; j < MYLENGTH - 1; j++)
		{
			if (CA_field[i][j].isAlive && !CA_field[i][j].chcecked)
			{
				index++;
				surfaceByIndex[index] = count_surface(i, j, index);
			}
		}

	for (int i = 1; i <= index; i++)
	{
		if (surfaceByIndex[i] > maxSurf)
		{
			maxSurf = surfaceByIndex[i];
			maxSurfInd = i;
		}
	}

	for (int i = 1; i < MYHEIGHT - 1; i++)
		for (int j = 1; j < MYLENGTH - 1; j++)
			if (CA_field[i][j].caveIndex != maxSurfInd)
				CA_field[i][j].isAlive = false;

	int maxSurfPerc = (int)(((double)maxSurf / (MYHEIGHT * MYLENGTH) ) * 100);
	if (maxSurfPerc < MIN_CAVE_SIZE_PERCENT)
		return true;
	return false;
}

int CA_cave_gen::count_surface(int y, int x, int index)
{
	int surface = 1;
	bool finished = false;
	std::vector <CA_Place*> CAVE;
	CAVE.push_back(&CA_field[y][x]);

	CA_field[y][x].chcecked = true;
	CA_field[y][x].caveIndex = index;

	while (!finished)
	{
		for (unsigned int i = 0; i < CAVE.size(); i++)
		{
			CA_Place* next = next_in_cave(CAVE[i]->y, CAVE[i]->x);
			if (next)
			{
				next->chcecked = true;
				next->caveIndex = index;
				CAVE.push_back(next);
				surface++;
			}
		}

		finished = true;
		for (unsigned int i = 0; i < CAVE.size(); i++)
			if (next_in_cave(CAVE[i]->y, CAVE[i]->x))
				finished = false;
	}
	return surface;
}

CA_Place* CA_cave_gen::next_in_cave(int y, int x)
{
	if (CA_field[y - 1][x].isAlive && !CA_field[y - 1][x].chcecked)
		return &CA_field[y - 1][x];
	else if (CA_field[y - 1][x - 1].isAlive && !CA_field[y - 1][x - 1].chcecked)
		return &CA_field[y - 1][x - 1];
	else if (CA_field[y - 1][x + 1].isAlive && !CA_field[y - 1][x + 1].chcecked)
		return &CA_field[y - 1][x + 1];
	else if (CA_field[y][x - 1].isAlive && !CA_field[y][x - 1].chcecked)
		return &CA_field[y][x - 1];
	else if (CA_field[y][x + 1].isAlive && !CA_field[y][x + 1].chcecked)
		return &CA_field[y][x + 1];
	else if (CA_field[y + 1][x].isAlive && !CA_field[y + 1][x].chcecked)
		return &CA_field[y + 1][x];
	else if (CA_field[y + 1][x - 1].isAlive && !CA_field[y + 1][x - 1].chcecked)
		return &CA_field[y + 1][x - 1];
	else if (CA_field[y + 1][x + 1].isAlive && !CA_field[y + 1][x + 1].chcecked)
		return &CA_field[y + 1][x + 1];
	else
		return nullptr;
}

void CA_cave_gen::reset_CA_field()
{
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
		{
			CA_field[i][j].isAlive = false;  
			CA_field[i][j].isAliveNext = false;
			CA_field[i][j].chcecked = false;
			CA_field[i][j].caveIndex = 0;
		}
}


