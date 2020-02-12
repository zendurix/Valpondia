#include "pch.h"
#include "Character.h"


void Character::set_staysOn (SharedPtr<Place> set)
{ staysOn = set; this->set_x(set->get_x()); this->set_y(set->get_y()); }


void Character::loadTexture(sf::Sprite sprite)
{
	spriteChar = sprite;
}

Character* Character::move_and_attack(char direction)
{
	SharedPtr<Place>  goingTo;
	short prevX = posX, prevY = posY;
	SharedPtr<Place>  fieldPrev = (*fieldArr)[posY][posX];
	switch (direction)
	{
	case '8':	posY--;				break;	
	case '9':	posY--;  posX++;	break;
	case '6':			 posX++;	break;
	case '3':	posY++;  posX++;	break;
	case '2':	posY++;				break;
	case '1':	posY++;	 posX--;	break;
	case '4':			 posX--;	break;
	case '7':	posY--;  posX--;	break;
	case '5':						break;	 /*'5' is for wait one turn*/	
	}

	if (posX < 0) posX = 0;
	if (posY < 0) posY = 0;
	if (posX == MYLENGTH) posX = MYLENGTH - 1;
	if (posY == MYHEIGHT) posY = MYHEIGHT - 1;

	goingTo = (*fieldArr)[posY][posX];

	if (prevX != posX || prevY != posY)
	{
		if (goingTo->get_isObstacle())
		{
			posX = prevX;
			posY = prevY;
			fieldPrev->go_here(this);
			moved = true;
		}
		else if (goingTo->get_characterHere() != nullptr)
		{
			posX = prevX;
			posY = prevY;
			fieldPrev->go_here(this);
			moved = true;
			return goingTo->get_characterHere();
		}
		else
		{
			staysOn = goingTo;
			goingTo->go_here(this);
			fieldPrev->leave_here();
			moved = true;
		}
	}
	return nullptr;
}

DMG Character::do_attack()
{
	DMG dmg = { 0, 0, 0 };
	if (equipped[static_cast<int>(BodyPart::rHand)] != nullptr)
	{
		dmg.baseDMG += equipped[static_cast<int>(BodyPart::rHand)]->melee.hit_baseDMG();
		dmg.fireDMG += equipped[static_cast<int>(BodyPart::rHand)]->melee.hit_fireDMG();
		dmg.penetration = equipped[static_cast<int>(BodyPart::rHand)]->melee.hit_penetration();
	}
	if (equipped[static_cast<int>(BodyPart::lHand)] != nullptr)
	{
		dmg.baseDMG += equipped[static_cast<int>(BodyPart::lHand)]->melee.hit_baseDMG();
		dmg.fireDMG += equipped[static_cast<int>(BodyPart::lHand)]->melee.hit_fireDMG();
		dmg.penetration = equipped[static_cast<int>(BodyPart::lHand)]->melee.hit_penetration();
	}

	if (equipped[static_cast<int>(BodyPart::lHand)] != nullptr && equipped[static_cast<int>(BodyPart::rHand)] != nullptr)
		dmg.penetration = (equipped[static_cast<int>(BodyPart::rHand)]->melee.hit_penetration() +
						   equipped[static_cast<int>(BodyPart::lHand)]->melee.hit_penetration()) / 2;

	strength = 1;

	dmg.penetration += strength;

	return dmg;
}


DEF Character::do_defend()
{
	DEF def = { 0, 0 };
	for (SharedPtr<Item> item : equipped)
	{
		if (item != nullptr)
		{
			def.baseDEF += item->defend.def_baseArmor();
			def.fireDEF += item->defend.def_fireArmor();
		}
	}

	// + bonuses

	return def;	 
}


bool Character::do_dodge()
{
	agility = 2;
	int dodge = 0;
	dodge += agility;

	for (SharedPtr<Item> item : equipped)
	{
		if (item != nullptr)
			dodge += item->defend.get_dodgeValue();
	}

	// + bonus for not heav inventory

	dodge *= 2;

	bool dodged = (random(0, 100) <= dodge);

	return dodged;
}

void Character::take_damage(int damage)
{
	hpLeft -= damage;
	if (hpLeft <= 0)
		DIE();
}

void Character::DIE()
{
	isAlive = false;
}


void Character::pick_item(SharedPtr<Item> item)
{
	inventory.push_back(item);
}



void Character::drop_item(SharedPtr<Item> item)
{
	SharedPtr<Item> drop = vector_pop2(inventory, item);
	staysOn->drop_here(drop);
}


void Character::equip_item(SharedPtr<Item> item, BodyPart part)
{
	if (item->get_twohand())
	{
		if     (equipped[(int)BodyPart::lHand])	
		{
			un_equip_item(equipped[(int)BodyPart::lHand], BodyPart::lHand);
		}
		else if (equipped[(int)BodyPart::rHand])	
		{
			un_equip_item(equipped[(int)BodyPart::rHand], BodyPart::rHand);
		}

		equipped[(int)BodyPart::rHand] = item;

		SharedPtr<Item> twohandcopy = std::make_shared<Item>(*item);
		MyText name = item->get_name();
		name.set_color_all(MCOL::grey);
		twohandcopy->set_name(name);

		equipped[(int)BodyPart::lHand] = twohandcopy;
	}
	else
	{
		if (equipped[(int)part])
			un_equip_item(equipped[(int)part], part);
		equipped[(int)part] = item;
	}
	vector_pop2(inventory, item);

	item->set_wornOnBodyPart(part);
	item->set_isWorn(true);

	armorBasic += item->defend.def_baseArmor();
	dodgeBonus += item->defend.get_dodgeValue();

}

void Character::un_equip_item(SharedPtr<Item> item, BodyPart part)
{
	if (item->get_twohand())
	{
		inventory.push_back(equipped[(int)BodyPart::rHand]);
		equipped[(int)BodyPart::lHand] = nullptr;
		equipped[(int)BodyPart::rHand] = nullptr;
	}
	else
	{
		inventory.push_back(item);
		equipped[(int)part] = nullptr;
	}

	armorBasic -= item->defend.def_baseArmor();
	dodgeBonus -= item->defend.get_dodgeValue();

	item->set_isWorn(false);
	item->set_wornOnBodyPart(BodyPart::none);
}

