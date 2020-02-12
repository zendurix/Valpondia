#pragma once

#include "Item.h"

#include "ItemsFlavorTexts.h"

class Items
{
private:
	typedef std::pair<std::string, sf::Color> strCol;
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;

public:
	// weapons

	inline static const Item swordHilt = Item(itemType::weapon, BodyPart::forHands, itemMaterial::iron, 1, 0, MyText(strCol("broken sword hilt", MCOL::slatGrey)),
		swordHiltText, '/', false, Attack(1, 1));

	inline static const Item steelSword = Item(itemType::weapon, BodyPart::forHands, itemMaterial::steel, 2, 5, MyText(strCol("sword", COL::White)),
		strCol("", COL::White), '/', false, Attack(3, 5));

	inline static const Item steelSword2h = Item(itemType::weapon, BodyPart::forHands, itemMaterial::steel, 4, 8, MyText(strCol("two hand sword", COL::White)),
		strCol("", COL::White), '/', true,  Attack(4, 7));

	inline static const Item cardboardSword = Item(itemType::weapon, BodyPart::forHands, itemMaterial::cardboard, 0, 0, MyText(strCol("sword", COL::White)),
		cardboardSwordText,  '/', false, Attack(0, 0));

	// armors	

	inline static const Item cardboardHelmet = Item(itemType::armor, BodyPart::head, itemMaterial::cardboard, 0, 0, MyText(strCol("helmet", COL::White)),
		strCol("", COL::White), '[', false, Attack(0, 0), Attack(0, 0), Defend(1, 0));

	inline static const Item rubberTrousers = Item(itemType::armor, BodyPart::legs, itemMaterial::rubber, 4, 15, MyText(strCol("trousers", COL::White)),
		strCol("", COL::White), '[', false, Attack(0, 0), Attack(0, 0), Defend(3, 0));

};

