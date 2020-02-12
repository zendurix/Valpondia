#include "pch.h"
#include "CharacterPlayer.h"



CharacterPlayer::CharacterPlayer(short x, short y, std::vector<std::vector<SharedPtr<Place> >> *field)
{

	armorBasic = 0;


	name = "zendurix";
	hpMax = 37;
	hpLeft = 21;

	posX = x;
	posY = y;
	printFormat = '@';

	isAI = false;
	moved = false;
	isAlive = true;
	
	fieldArr = field;

	view = 100;

	staysOn = (*fieldArr)[y][x];
	(*fieldArr)[y][x]->go_here(this);
}


CharacterPlayer::~CharacterPlayer()
{
}
