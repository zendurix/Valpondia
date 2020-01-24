#pragma once

#include "Character.h"


class CharacterPlayer :	public Character
{

public:
	CharacterPlayer(short x, short y, std::vector<std::vector<std::shared_ptr<Place> >> *field);
	~CharacterPlayer();
};


