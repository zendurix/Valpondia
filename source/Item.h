#pragma once


#include "MyText.h"
#include "ItemComp.h"






class Item
{
private:
	typedef std::pair<std::string, sf::Color> strCol;
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;

#define MTXTINIT MyText(strCol

	//inline static const MyText itemTypes[] = { MTXTINIT("weapon", COL::White)), MTXTINIT("aromr", COL::White)), MTXTINIT("potion", COL::White)) };
	inline static const std::string itemTypes[] = { "weapon", "aromr", "potion" };
	inline static const MyText itemTMaterials[] = { MTXTINIT("cardboard", MCOL::grey)), MTXTINIT("nonSpecific", COL::White)),
		MTXTINIT("cloth", COL::Yellow)), MTXTINIT("leather", MCOL::brown)), MTXTINIT("iron", MCOL::slatGrey)), MTXTINIT("rubber", MCOL::yellowLight)) ,
		MTXTINIT("steel", COL::White)) };

	itemType type;
	itemMaterial material;


	int weight;
	int value;

	bool isWorn;
	BodyPart wornOnBodyPart;

	std::string flavorText;
	MyText name; 

	BodyPart bodyPart;
	bool twoHand;

	bool twoHanded;


public:

	char printFormat;

	Item(itemType Ittype, BodyPart bodypart, itemMaterial Itmaterial, int Itweight, int Itvalue, 
		MyText name = strCol("", COL::White), std::string text = "", char printForm = ' ', bool twohand = false,
		Attack mele = Attack(), Attack rang = Attack(), Defend def = Defend(), Use us = Use() );
	~Item();



	// item can have multiple abilities, depending on components:
	Attack melee;
	Attack ranged;
	Defend defend;
	Use    use;


	// getters
	bool get_isWorn()				const { return isWorn; }
	MyText get_name()				const { return name; }
	itemType get_type()				const { return type; }
	BodyPart get_bodyPart()			const { return bodyPart; }
	BodyPart get_wornOnBodyPart()	const { return wornOnBodyPart; }
	bool get_twohand()				const { return twoHand; }


	// setters
	void set_name(MyText set)				{ name = set; }
	void set_isWorn(bool set)				{ isWorn = set; }
	void set_bodyPart(BodyPart set)			{ bodyPart = set; }
	void set_wornOnBodyPart(BodyPart set)	{ wornOnBodyPart = set; }
};

