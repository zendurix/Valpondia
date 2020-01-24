#include "pch.h"
#include "CharacterEnemy.h"




CharacterEnemy::CharacterEnemy(short x, short y, std::vector<std::vector<std::shared_ptr<Place> >> *field)
{
	posX = x;
	posY = y;
	isAI = true;
	moved = false;
	isAlive = true;
	printFormat = '@';
	isAlive = true;

	fieldArr = field;

	view = 10;

	staysOn = (*fieldArr)[y][x];
	(*fieldArr)[y][x]->go_here(this);
}


CharacterEnemy::~CharacterEnemy()
{
	//LOG(name << " died at x:" << posX << " y:" << posY);
}



void CharacterEnemy::choose_what_to_do()
{
	// determine actions acourding to attitude, and items/ character in view range

}


void CharacterEnemy::follow_target_Astar(std::shared_ptr<Place> target)
{
	char moveDir = '5';
	if (distance_meter(*this->get_staysOn(), *target) > 2.0)
	{
		moveDir = PathFinding::best_dir(*this, target);
	}
	move(moveDir);
}


void CharacterEnemy::follow_target_shortest_way(std::shared_ptr<Place> target)
{
	char directions[8] = { '8', '9', '6', '3', '2', '1', '4', '7' };
	double distances[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	char dir = '5';

	calcullate_distances_for_following(distances, target);

	moved = false;
	int bestDistanceID = 0;

	int errorCount = 0;

	while (1)
	{
		if (moved)
		{
			break;
		}

		for (int i = 0; i < 8; i++)
		{
			errorCount++;
			if (errorCount > 20)
			{
				break;
			}
			if (distances[i] == *std::min_element(distances, distances + 8)) // parameters are ptr to begining, and end of array
			{
				bestDistanceID = i;
				break;
			}
		
		}			
		if (errorCount > 20)
		{
			dir = '5';
		}
		else
		{
			dir = directions[bestDistanceID];
		}

		move(dir);
	}
}



void CharacterEnemy::calcullate_distances_for_following(double* distanceArr,std::shared_ptr<Place> target)
{
	posY -= 1;
	distanceArr[0] = distance_meter(*this, *target);
	posY += 1;

	posY += 1;
	distanceArr[4] = distance_meter(*this, *target);
	posY -= 1;

	posX -= 1;
	distanceArr[6] = distance_meter(*this, *target);
	posX += 1;

	posX += 1;
	distanceArr[2] = distance_meter(*this, *target);
	posX -= 1;

	posY -= 1;
	posX += 1;
	distanceArr[1] = distance_meter(*this, *target);
	posY += 1;
	posX -= 1;

	posY += 1;
	posX += 1;
	distanceArr[3] = distance_meter(*this, *target);
	posY -= 1;
	posX -= 1;

	posY += 1;
	posX -= 1;
	distanceArr[5] = distance_meter(*this, *target);
	posY -= 1;
	posX += 1;

	posY -= 1;
	posX -= 1;
	distanceArr[7] = distance_meter(*this, *target);
	posY += 1;
	posX += 1;
}