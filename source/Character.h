#pragma once

#include "CONFIGURATION.h"
#include "Place.h"
#include "Item.h"

class Place;


class Character
{
protected:
	std::vector<std::vector<SharedPtr<Place> >> *fieldArr;
	int onLevelID;

	sf::String name;
	sf::Sprite spriteChar;

	bool moved,
		 isAI,
		 isAlive;
	short posX, posY;
	char printFormat;
	SharedPtr<Place>  staysOn;

	short hpMax,
		  hpLeft,
		  attack,
		  agility,
		  inteligence,
		  view;

	float speed;
	
	SharedPtr<Item> equipped[BODY_PARTS_COUNT]; // ID==BodyPart : {head = 0, body, hands, legs, lHand, rHand, none};

	std::vector< SharedPtr<Item>> inventory;
	
public:
	//Character() = default;

	void loadTexture(sf::Sprite sprite);

	void move(char direction);
	void attack_character(Character* target);
	void take_damage(int damage);
	void virtual DIE();

	void pick_item(SharedPtr<Item> item);
	void drop_item(SharedPtr<Item> item);

	void equip_item(SharedPtr<Item> item, BodyPart part);
	void un_equip_item(SharedPtr<Item> item, BodyPart part);


// getters:
	bool get_isAI() { return isAI; }
	short get_x() { return posX; }
	short get_y() { return posY; }
	SharedPtr<Place>  get_staysOn() { return staysOn; }
	char get_printFormat() { return printFormat; }
	int get_view() { return view; }
	int get_onLevelID() { return onLevelID; };
	sf::Sprite get_spriteChar() { return spriteChar; }

	std::vector< SharedPtr<Item>>* get_inventory_ref() { return &inventory; }
	SharedPtr<Item>* get_equipped_ref() { return equipped; }

// setters:
	void set_x(short set) { posX = set; }
	void set_y(short set) { posY = set; }
	void set_staysOn(SharedPtr<Place>  set) { staysOn = set; }
	void set_printFormat(char set) { printFormat = set; }
	void set_onLevelID(int set) { onLevelID = set; }
	sf::Sprite set_spriteChar(sf::Sprite set) { spriteChar = set; }

	void set_fieldArr(std::vector<std::vector<SharedPtr<Place> >> *field) { fieldArr = field; }
};









template <typename T>
T vector_pop2(std::vector<T> &vec, T elem)
{
	int pos = std::distance(vec.begin(), std::find(vec.begin(), vec.end(), elem));
	T ret = vec.at(pos);
	vec.erase(vec.begin() + pos);
	return ret;
}