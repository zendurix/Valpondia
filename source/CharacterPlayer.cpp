#include "pch.h"
#include "CharacterPlayer.h"



CharacterPlayer::CharacterPlayer(short x, short y, std::vector<std::vector<SharedPtr<Place> >> *field)
{
	posX = x;
	posY = y;
	printFormat = '@';

	isAI = false;
	moved = false;
	isAlive = true;
	
	fieldArr = field;

	view = 20;

	staysOn = (*fieldArr)[y][x];
	(*fieldArr)[y][x]->go_here(this);
}


CharacterPlayer::~CharacterPlayer()
{
}
