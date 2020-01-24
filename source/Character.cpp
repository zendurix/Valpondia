#include "pch.h"
#include "Character.h"


void Character::loadTexture(sf::Sprite sprite)
{
	spriteChar = sprite;
	
	;
}

void Character::move(char direction)
{
	std::shared_ptr<Place>  field;
	short prevX = posX, prevY = posY;
	std::shared_ptr<Place>  fieldPrev = (*fieldArr)[posY][posX];
	switch (direction)
	{
	case '8':
		posY--;
		break;
	case '9':
		posY--;
		posX++;
		break;
	case '6':
		posX++;
		break;
	case '3':
		posY++;
		posX++;
		break;
	case '2':
		posY++;
		break;
	case '1':
		posY++;
		posX--;
		break;
	case '4':
		posX--;
		break;
	case '7':
		posY--;
		posX--;
		break;
	case '5':    // '5' is for wait one turn
		break;
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


void Character::pick_item(std::shared_ptr<Item> item)
{
	inventory.push_back(item);
}



void Character::drop_item(std::shared_ptr<Item> item)
{
	std::shared_ptr<Item> drop = vector_pop2(inventory, item);
	staysOn->drop_here(drop);
}


void Character::equip_item(std::shared_ptr<Item> item, BodyPart part)
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

		std::shared_ptr<Item> twohandcopy = std::make_shared<Item>(*item);
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
}

void Character::un_equip_item(std::shared_ptr<Item> item, BodyPart part)
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
}