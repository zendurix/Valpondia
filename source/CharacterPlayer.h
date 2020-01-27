#pragma once

#include "Character.h"


class CharacterPlayer :	public Character
{

public:
	CharacterPlayer(short x, short y, std::vector<std::vector<SharedPtr<Place> >> *field);
	~CharacterPlayer();
};


