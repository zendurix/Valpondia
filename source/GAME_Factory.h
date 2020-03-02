#pragma once


#include "GAME.h"
#include "ECS/ECS_Coordinator.h"





class GAME_Factory
{
	friend class GAME;

private:
	inline static std::vector <sf::Sprite>* texturesPtr;

	GAME& g;

	GAME_Factory(GAME& game, std::vector <sf::Sprite>* texturesPointer);
	~GAME_Factory();
public:

	Entity make_rat(Position pos);



};

