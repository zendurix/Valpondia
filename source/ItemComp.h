#pragma once

#include "CONFIGURATION.h"
#include "RNG.h"


class Attack
{
private:

	int minDmg;
	int maxDmg;

public:
	Attack(int minD = 0, int maxD = 0) : minDmg(minD), maxDmg(maxD) {}
	~Attack() {}

	int hit() const { return random(minDmg, maxDmg); }

};



class Defend
{
private:
	//friend class Item;

	int baseArmor;
	int dodgeValue;
	

public:
	Defend(int armor = 0, int dodge = 0)
		: baseArmor(armor), dodgeValue(dodge) {}
	~Defend() {}


	// getters
	int get_baseArmor()		const { return baseArmor; }
	int get_dodgeValue()    const { return dodgeValue; }


};


class Use
{
private:
	//friend class Item;
	useType type;

public:
	Use(useType us = useType::noUse) : type(us) {}
	~Use() {}

	void use();

};


class UseDrink : Use
{
private:
	//friend class Item;

public:
	

};