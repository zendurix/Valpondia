#include "pch.h"
#include "UI.h"

#include "general_purpose_func.h"

int UI::center_text_posX(sf::Text text, int centeringLength)
{
	int charLength = get_char_length(text);
	int size = text.getString().getSize();
	int posX = centeringLength / 2 - (size / 2) * (charLength + 1);
	return posX;
}
int UI::center_text_posX(MyText text, int centeringLength)
{
	int charLength = text.get_charLength();
	int size = text.get_string().size();
	int posX = centeringLength / 2 - (size / 2) * (charLength + 4);
	return posX;
}

int UI::center_text_posY(sf::Text text, int centeringHeight)
{
	int charHeight = get_char_height(text);
	int posY = centeringHeight / 2 - (charHeight / 2);
	return posY;
}


sf::Color UI::get_hp_color(const Character& character)
{
	int hpProc = ((double)character.get_hpLeft() / (double)character.get_hpMax()) * 100.0;

	if (hpProc == 100)		return MCOL::hpProc100;
	else if (hpProc >= 80)	return MCOL::hpProc80;
	else if (hpProc >= 60)	return MCOL::hpProc60;
	else if (hpProc >= 40)	return MCOL::hpProc40;
	else if (hpProc >= 20)	return MCOL::hpProc20;
	else					return MCOL::hpProc0;

}










void UI::init_UI(sf::RenderWindow* win)
{
	if (!initialized)
	{
		initialized = true;

		window = win;

		init_windows();
		init_texts();
		LOG("User Interface.....................initialized");
	}
}


void UI::init_windows()
{
	const int outThicc = 5;
	playerUIWin = sf::RectangleShape(sf::Vector2f(UI_LENGTH - 2 * outThicc, WIN_HEIGHT - 2 * outThicc));
	playerUIWin.setFillColor(MCOL::slatGrey);
	playerUIWin.setOutlineColor(MCOL::brown);
	playerUIWin.setOutlineThickness(outThicc);
	playerUIWin.setPosition(WIN_LENGTH - UI_LENGTH + outThicc, outThicc);
}

void UI::init_texts()
{
	text = init_text();
	myText = MyText(strCol("", COL::White), 32, 0, 0, MyText::get_STD_FONT());
	invTitle = MyText(strCol("INVENTORY", COL::Yellow), 32, 0, 0, MyText::get_STD_FONT());
}










void UI::draw_player_UI(const CharacterPlayer& player)
{
	window->draw(playerUIWin);

	int posX = WIN_LENGTH - UI_LENGTH + 10;;
	
	myText.clear();
	myText = strCol(player.get_name(), COL::White);
	myText.setPosition(posX, 20);
	myText.window_draw(window);

	myText.clear();
	std::string hpStr = std::to_string(player.get_hpLeft()) + "/" + std::to_string(player.get_hpMax());
	myText = strCol("HP:", COL::White);
	static sf::Color hpColor = get_hp_color(player);
	myText += strCol(hpStr, hpColor);
	myText.setPosition(posX, 50);
	myText.window_draw(window);

	myText.clear();
	myText = strCol("ARMOR: " + std::to_string(player.get_armorBasic()), COL::White);
	myText.setPosition(posX, 80);
	myText.window_draw(window);
}













std::vector<int> UI::pickUp_items_selector(const std::vector<SharedPtr<Item>>* itemToChoose)
{
	std::vector<int> choosenIndexes;
	std::vector<MyText> itemTexts;
	for (auto item : *itemToChoose)
		itemTexts.push_back(item->get_name());

	MyText title = strCol("PICK", MCOL::brown);
	int charHeight = title.get_charHeight();

	UIWindow UIwin(500, 400, 100, 100, title, itemTexts, charHeight);
	UIwin.add_tickBoxes();
	choosenIndexes = UIwin.call_window_return_choosen_indexes(window);

	return choosenIndexes;
}











int UI::player_inventory_selector(const std::vector< SharedPtr<Item>>* inv)
{
	int ret;
	int choosenIndex;
	std::vector<MyText> itemTexts;
	MyText title = strCol("INVENTORY", MCOL::limeGreen);

	for (auto item : *inv)
		itemTexts.push_back(item->get_name());
	int charHeight = title.get_charHeight();

	UIWindow UIwin(WIN_LENGTH, WIN_HEIGHT, 0, 0, title, itemTexts, charHeight, false, 10);
	choosenIndex = UIwin.call_window_return_choosen_indexes(window)[0];

	return choosenIndex;
}















ItemOpt UI::item_options_selector(SharedPtr<Item> item)
{
	int optionsSize;
	std::vector<MyText> options = { strCol("look", COL::White), strCol("drop", COL::White) };
	options.push_back( item->get_isWorn() ? strCol("unequip", COL::White) : strCol("equip", COL::White ));
	optionsSize = 3;
	if (item->use.get_type() != useType::noUse)
	{
		options.push_back(strCol("use", COL::White));
		optionsSize = 4;
	}

	int x = 420;
	int y = 340;
	int winLength = 500;
	int winHeight = 300;
	ItemOpt ret;

	MyText title = item->get_name();
	int charHeight = title.get_charHeight();

	UIWindow UIwin(winLength, winHeight, x, y, title, options, charHeight);

	int choosenIndex = UIwin.call_window_return_choosen_indexes(window)[0];

	if		(choosenIndex == -1)							  ret = ItemOpt::none;
	else if	(options[choosenIndex].get_string() == "look")	  ret = ItemOpt::look;
	else if (options[choosenIndex].get_string() == "drop")	  ret = ItemOpt::drop;
	else if (options[choosenIndex].get_string() == "equip")	  ret = ItemOpt::equip;
	else if (options[choosenIndex].get_string() == "unequip") ret = ItemOpt::unequip;
	else if (options[choosenIndex].get_string() == "use")	  ret = ItemOpt::use;

	return ret;
}
















BodyPart UI::choose_bodyPart_to_equip(const SharedPtr<Item> item, const SharedPtr<Item>* eq)
{
	std::string optionsStrings[BODY_PARTS_COUNT] = { "head   ", "body   ", "hands  ", "legs   ", "rHand  ", "lHand  " };
	//int size = BODY_PARTS_COUNT;

	BodyPart itemForBodyPart = item->get_bodyPart();
	BodyPart ret;

	std::vector<MyText> options;
	std::vector<int> aviableOptIndexes;
	aviableOptIndexes.reserve(2);

	if (itemForBodyPart == BodyPart::forHands)
	{
		aviableOptIndexes.push_back(static_cast<int>(BodyPart::rHand));
		aviableOptIndexes.push_back(static_cast<int>(BodyPart::lHand));
	}
	else
		aviableOptIndexes.push_back(static_cast<int>(itemForBodyPart));

	for (int index : aviableOptIndexes)
	{
		myText.clear();
		myText = strCol(optionsStrings[index], COL::White);
		myText += (eq[index]) ? eq[index]->get_name() : strCol("none ", MCOL::grey);
		options.push_back(myText);
	}
	MyText title = strCol("Equip: ", COL::White);
	title += item->get_name();
	int charHeight = title.get_charHeight();

	int x = 400;
	int y = 300;
	int winLength = 600;
	int winHeight = aviableOptIndexes.size() * (charHeight + 10) + 50;

	UIWindow UIwin(winLength, winHeight, x, y, title, options, charHeight);
	int bodyPartIndex = UIwin.call_window_return_choosen_indexes(window)[0];

	if (bodyPartIndex != -1)
		bodyPartIndex = aviableOptIndexes[bodyPartIndex];
	ret = static_cast<BodyPart>(bodyPartIndex);
	return ret;
}











BodyPart UI::player_equipment_selector(const SharedPtr<Item>* eq)
{
	std::string optionsStr[BODY_PARTS_COUNT] = { "head   ", "body   ", "hands  ", "legs   ", "rHand  ", "lHand  " };
	BodyPart ret;

	MyText title = strCol("EQUIPMENT: ", MCOL::lawnGreen);
	int charHeight = title.get_charHeight();

	std::vector<MyText> options;
	for (int i = 0; i < BODY_PARTS_COUNT; i++ )
	{
		myText.clear();		
		myText = strCol(optionsStr[i], COL::White);
		myText += (eq[i]) ? eq[i]->get_name() : strCol("none ", MCOL::grey);
		options.push_back(myText);
	}

	int x = 200;
	int y = 300;
	int winLength = 800;
	int winHeight = BODY_PARTS_COUNT * (CHAR_SIZE + 10);


	UIWindow UIwin(winLength, winHeight, x, y, title, options, charHeight);
	int bodyPartIndex = UIwin.call_window_return_choosen_indexes(window)[0];
	ret = static_cast<BodyPart>(bodyPartIndex);
	return ret;
}




int UI::equip_from_inv_selector(BodyPart bodyPartToEquip, const std::vector<SharedPtr<Item>>* inv)
{
	std::string bodyPartsStr[BODY_PARTS_COUNT] = { "head   ", "body   ", "hands  ", "legs   ", "rHand  ", "lHand  " };
	MyText title = strCol("Equip to: ", COL::White);
	std::vector<std::array<int, 2>> invIndexAndOptIndex;;
	title += strCol(bodyPartsStr[static_cast<int>(bodyPartToEquip)], COL::White);
	int charHeight = title.get_charHeight();

	std::vector<MyText> options;
	for (int i = 0, j = 0; i < inv->size(); i++)
	{
		if (bodyPartToEquip == BodyPart::lHand || bodyPartToEquip == BodyPart::rHand)
			if ((*inv)[i]->get_bodyPart() == BodyPart::forHands)
			{
				options.push_back((*inv)[i]->get_name());
				invIndexAndOptIndex.push_back({ i, j });
				j++;
			}
		if ((*inv)[i]->get_bodyPart() == bodyPartToEquip)
		{
			options.push_back((*inv)[i]->get_name());
			invIndexAndOptIndex.push_back({ i, j });
			j++;
		}
	}

	int x = 100;
	int y = 300;
	int winLength = 600;
	int winHeight = 400;

	UIWindow UIwin(winLength, winHeight, x, y, title, options, charHeight);
	int choosenIndex = UIwin.call_window_return_choosen_indexes(window)[0];

	for (int i = 0; i < invIndexAndOptIndex.size(); i++)
	{
		if (invIndexAndOptIndex[i][1] == choosenIndex)
		{
			choosenIndex = invIndexAndOptIndex[i][0];
			break;
		}
	}

	return choosenIndex;
}



void UI::show_item_info(const SharedPtr<Item> item)
{
	MyText dmg, armor, dodge, name, flavortext;
	get_item_info_texts(item, dmg, armor, dodge, name, flavortext);

	std::vector<MyText> infoCombined = { flavortext, dmg, armor, dodge };

	int x = 300;
	int y = 100;
	int winLength = 600;
	int winHeight = 400;
	int charHeight = name.get_charHeight();

	UIWindow UIwin(winLength, winHeight, x, y, name, infoCombined, charHeight);
	UIwin.set_interactive(false);
	UIwin.call_window_return_choosen_indexes(window);
}



void UI::get_item_info_texts(const SharedPtr<Item> item, MyText& dmg, MyText& armor, MyText& dodge, MyText& name, MyText& flavortext)
{
	name = item->get_name();
	flavortext = item->get_flavorText();

	int dmgMin = item->melee.get_minDmg();
	int dmgMax = item->melee.get_maxDmg();
	dmg = strCol("Melee Damage: " + std::to_string(dmgMin) + "-" + std::to_string(dmgMax), COL::White);

	int basicArmor = item->defend.def_baseArmor();
	if (basicArmor != 0) armor = strCol("Armor: " + std::to_string(basicArmor), COL::White);
	else 				 armor = strCol("", COL::White);

	int dodgeValue = item->defend.get_dodgeValue();
	if (dodgeValue != 0) dodge = strCol("Dodge: " + std::to_string(dodgeValue), COL::White);
	else 				 dodge = strCol("", COL::White);
}
