#include "pch.h"
#include "Place.h"

short Place::countX = 0;
short Place::countY = 0;

Place::Place(short level)
{
	x = countX;
	y = countY;

	levelID = level;

	tileColor = MCOL::placeHolder;

	printFormat = STD_FLOOR;
	prevPrintFormat = STD_FLOOR;

	isObstacle = false;
	isDoors = false;
	isWall = false;
	isInRoom = false;
	visible = false;
	changedPrint = true;
	wasSeen = false;
	wasVisible = false;
	wasCheck = false;

	stairsDown = false;
	stairsUp = false;

	roomHere = nullptr;
	characterHere = nullptr;

	countX++;
	if (countX == MYLENGTH)
	{
		countX = 0;
		countY++;
	}
}


Place::~Place()
{

}

void Place::RESET_counters() //static method
{
	countX = 0;
	countY = 0;
}


void Place::go_here(Character* character)
{
	characterHere = character;
	printFormat = character->get_printFormat();
	changedPrint = true;
}

void Place::leave_here()
{
	characterHere = nullptr;
	changedPrint = true;
	pick_up(nullptr);
}

void Place::RESET()
{// restarts field to begining, clean state
	tileColor = MCOL::placeHolder;
	printFormat = STD_FLOOR;
	prevPrintFormat = STD_FLOOR;
	isObstacle = false;
	isInRoom = false;
	isWall = false;
	isDoors = false;
	changedPrint = false;

	characterHere = nullptr;
	visible = false;
	wasSeen = false;
	wasVisible = false;

	roomHere = nullptr;

	itemsHere.clear();
}


void Place::make_obstacle()
{
	isObstacle = true;
	printFormat = STD_WALL;
	prevPrintFormat = STD_WALL;
}

void Place::unmake_obstacle()
{
	isObstacle = false;
	printFormat = STD_FLOOR;
	prevPrintFormat = STD_FLOOR;
}

void Place::make_wall()
{
	isObstacle = true;
	isWall = true;
}

void Place::make_visible()
{
	if (!wasCheck)
	{
		if (wasVisible)
		{
			visible = true;
		}
		else
		{
			wasSeen = true;
			visible = true;
			wasCheck = true;
			wasVisible = true;
		}
	}
}

void Place::unmake_visible()
{
	visible = false;

}

void Place::drop_here(std::shared_ptr<Item> item)
{
	itemsHere.push_back(item);
	printFormat = item->printFormat;
	if (characterHere != nullptr)
		printFormat = characterHere->get_printFormat();
}

void Place::pick_up(std::shared_ptr<Item> item)
{
	if (item != nullptr)
		itemsHere.erase(std::find(itemsHere.begin(), itemsHere.end(), item));
	if (itemsHere.size() != 0)
		printFormat = itemsHere[0]->printFormat;
	else
		printFormat = prevPrintFormat;

	if (characterHere != nullptr)
		printFormat = characterHere->get_printFormat(); 
}