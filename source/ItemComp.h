#pragma once

#include "CONFIGURATION.h"
#include "RNG.h"


class Attack
{
private:

	int minDmg;
	int maxDmg;

	int fireDMG;

	int penetration;

public:
	Attack(int minD = 0, int maxD = 0) : minDmg(minD), maxDmg(maxD) { fireDMG = 1; penetration = 5; }
	~Attack() {}

	int hit_baseDMG()		const { return random(minDmg, maxDmg); }
	int hit_fireDMG()		const { return fireDMG; }
	int hit_penetration()	const { return penetration; }

	int get_minDmg() const { return minDmg; }
	int get_maxDmg() const { return maxDmg; }

};



class Defend
{
private:
	//friend class Item;

	int baseArmor;
	int fireArmor;
	int dodgeValue;
	

public:
	Defend(int armor = 0, int dodge = 0)
		: baseArmor(armor), dodgeValue(dodge)
	{
		fireArmor = 0;
	}
	~Defend() {}

	int def_baseArmor()		const { return baseArmor; }
	int def_fireArmor()		const { return fireArmor; }

	// getters
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

	useType get_type() { return type; }

};


class UseDrink : Use
{
private:
	//friend class Item;

public:
	

};