#pragma once

//#include "pch.h"

#include "Item.h"



class Items
{
private:
	typedef std::pair<std::string, sf::Color> strCol;
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;

public:
	// weapons

	inline static const Item swordHilt = Item(itemType::weapon, BodyPart::forHands, itemMaterial::iron, 1, 0, MyText(strCol("broken sword hilt", MCOL::slatGrey)),
		"", '/', false, Attack(1, 1));

	inline static const Item steelSword = Item(itemType::weapon, BodyPart::forHands, itemMaterial::steel, 2, 5, MyText(strCol("sword", COL::White)),
		"", '/', false, Attack(3, 5));

	inline static const Item steelSword2h = Item(itemType::weapon, BodyPart::forHands, itemMaterial::steel, 4, 8, MyText(strCol("two hand sword", COL::White)),
		"", '/', true,  Attack(4, 7));

	// armors	

	inline static const Item cardboardHelmet = Item(itemType::armor, BodyPart::head, itemMaterial::cardboard, 0, 0, MyText(strCol("helmet", COL::White)),
		"", '[', false, Attack(0, 0), Attack(0, 0), Defend(0, 0));

	inline static const Item rubberTrousers = Item(itemType::armor, BodyPart::legs, itemMaterial::rubber, 4, 15, MyText(strCol("trousers", COL::White)),
		"", '[', false, Attack(0, 0), Attack(0, 0), Defend(0, 0));

};

