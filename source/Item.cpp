#include "pch.h"
#include "Item.h"



Item::Item(itemType Ittype, BodyPart bodypart, itemMaterial Itmaterial, int Itweight, int Itvalue, 	MyText _name,
		   std::string text, char printForm, bool twohand, Attack mele, Attack rang, Defend def, Use us) :
	type(Ittype), material(Itmaterial), bodyPart(bodypart), weight(Itweight), flavorText(text),
	melee(mele), ranged(rang), defend(def), use(us), printFormat(printForm), twoHand(twohand)
{
	isWorn = false;
	wornOnBodyPart = BodyPart::none;

	value = Itvalue * (int)material;

	name += _name;
	name += MyText(strCol("   ", COL::White));
	name += MyText(strCol("(", COL::White));
	name += itemTMaterials[(int)material];
	name += MyText(strCol(")", COL::White));

	

}


Item::~Item()
{
}
