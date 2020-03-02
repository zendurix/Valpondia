#include "pch.h"
#include "Place.h"

#include "MAP_GEN/Room.h"
#include "UI/colors.h"



void Place::RESET_counters()
{
	countX = 0;
	countY = 0;
}

Place::Place(short level)
	: levelID(level)
{
	x = countX;
	y = countY;

	countX++;
	if (countX == MYLENGTH)
	{
		countX = 0;
		countY++;
	}

	RESET();
	update_sprite();
}
Place::~Place(){}




void Place::update_sprite()
{
	//   std::vector<sf::Sprite>* texturesUsed;
	//   if (!GAME_MODE_ASCII)
	//   	texturesUsed = texturesPtr;
	//   else
	//   	texturesUsed = texturesASCIIPtr;
	//   
	//   *toPrint = (*texturesUsed)[static_cast<int>(placeType)];
}




void Place::RESET()
{// restarts field to begining, clean state
	visible = false;
	wasSeen = false;
	//wasVisible = false;
	roomHere = nullptr;
	connector = NULLConnector;
	itemsHere.clear();

	entityCharHere = MAX_ENTITIES;
	obstacleHere = MAX_ENTITIES;

}





SharedPtr<sf::Sprite> Place::get_sprite_to_print()
{
	Entity entityToPrint;
	SharedPtr<sf::Sprite> sprite;

	// Priorioty of entities to print:
	if (obstacleHere != MAX_ENTITIES)
		entityToPrint = obstacleHere;
	else if (entityCharHere != MAX_ENTITIES)
		entityToPrint = entityCharHere;
	// items
	// floor
	else
		entityToPrint = MAX_ENTITIES;



	
	if (entityToPrint != MAX_ENTITIES)
	{
		sprite = ecsPtr->get_component<Render>(entityToPrint).renderSprite;
		sprite->setColor(ecsPtr->get_component<Render>(entityToPrint).spriteColor);
	}
	else
	{
		sprite = DEFAULT_FLOOR;
		sprite->setColor(sf::Color::White);
	}



	if (!visible)
	{
		if (wasSeen)
			sprite->setColor(MCOL::grey);
		else
			sprite->setColor(sf::Color::Black);
	}
	else
	{
		sprite->setColor(sf::Color::White);
	}

	return sprite;
}





void Place::go_here(Entity character)
{
	entityCharHere = character;
}

void Place::leave_here()
{
	entityCharHere = MAX_ENTITIES;
}




void Place::make_obstacle(ObstacleType type)
{
	SharedPtr<sf::Sprite> sprite;
	switch (type)
	{
	case ObstacleType::rock:
		sprite = std::make_shared<sf::Sprite>(texturesPtr->at(static_cast<int>(ObstacleType::rock)));

	}
	Entity obstacle = ecsPtr->create_entity();
	ecsPtr->add_component(obstacle, Obstacle{});
	ecsPtr->add_component(obstacle, Render{ sprite, sf::Color::White });
	obstacleHere = obstacle;
}

void Place::unmake_obstacle()
{
	if (obstacleHere != MAX_ENTITIES)
	{
		ecsPtr->destroy_entity(obstacleHere);
		obstacleHere = MAX_ENTITIES;
	}
}

void Place::make_wall()
{
	//isObstacle = true;
	//
	//placeType = PlaceType::brickWall;
	//update_sprite();
}

void Place::make_visible()
{
	//if (!wasCheck) // MDELETE
	//{
		//if (wasVisible)
		//{
		//	visible = true;
		//}
		//else
		//{
			wasSeen = true;
			visible = true;
			//wasCheck = true;
			//wasVisible = true;
		//}
	//}
}

void Place::unmake_visible()
{
	visible = false;
}

//void Place::drop_here(SharedPtr<Item> item)
//{
//	itemsHere.push_back(item);
//}
//
//void Place::pick_up(SharedPtr<Item> item)
//{
//	if (item != nullptr)
//		itemsHere.erase(std::find(itemsHere.begin(), itemsHere.end(), item));
//}