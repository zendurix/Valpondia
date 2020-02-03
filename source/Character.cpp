#include "pch.h"
#include "Character.h"


void Character::loadTexture(sf::Sprite sprite)
{
	spriteChar = sprite;
}

void Character::move(char direction)
{
	SharedPtr<Place>  field;
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

	field = (*fieldArr)[posY][posX];

	if (prevX != posX || prevY != posY)
	{
		if (!field->get_isObstacle())
		{
			staysOn = field;
			field->go_here(this);
			fieldPrev->leave_here();
			moved = true;
		}
		else
		{
			posX = prevX;
			posY = prevY;
			fieldPrev->go_here(this);
			moved = true;
		}
	}
}

void Character::attack_character(Character* target)
{
	int dmg = attack;
	target->take_damage(dmg);
}

void Character::take_damage(int damage)
{
	int damageDone = damage;
	hpLeft -= damageDone;
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

	armorBasic += item->defend.get_baseArmor();
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

	armorBasic -= item->defend.get_baseArmor();
	dodgeBonus -= item->defend.get_dodgeValue();

	item->set_isWorn(false);
	item->set_wornOnBodyPart(BodyPart::none);
}

