#pragma once

// User Interface class

#include "UIWindow.h"
#include "MyText.h"
#include "Character.h"
#include "CharacterPlayer.h"

class UIWindow;


class UI // static class
{
private:	
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;


	inline static bool initialized = false; 

	inline static sf::RenderWindow* window;
	
	inline static sf::RectangleShape blackWin;
	inline static sf::RectangleShape smallBlackWin;
	inline static sf::RectangleShape fullBlackWin;
	inline static sf::RectangleShape bodyPartBlackWin;

	inline static sf::RectangleShape playerUIWin;

	//inline static sf::RectangleShape tickBox;


	inline static sf::Text *text;

	inline static MyText myText;



	inline static MyText invTitle = MyText();

	// PRIVATE FUNCTIONS:
	static void init_windows();
	static void init_texts();

	static sf::Color get_hp_color(const Character& character);

	static int center_text_posX(sf::Text text, int centeringLength = WIN_LENGTH);
	static int center_text_posX(MyText text, int centeringLength = WIN_LENGTH);
	static int center_text_posY(sf::Text text, int centeringHeight = WIN_HEIGHT);

	static void get_item_info_texts(const SharedPtr<Item> item, MyText& dmg, MyText& armor, MyText& dodge, MyText& name, MyText& flavortext);

// private

public:
	UI() = delete;

	static void init_UI(sf::RenderWindow* win);

	static void draw_player_UI(const CharacterPlayer& player);

	static std::vector<int> pickUp_items_selector(const std::vector<SharedPtr<Item>>* itemToChoose);

	static int player_inventory_selector(const std::vector<SharedPtr<Item>>* inventory);

	static BodyPart player_equipment_selector(const SharedPtr<Item>* equpment);

	static BodyPart choose_bodyPart_to_equip(const SharedPtr<Item> item, const SharedPtr<Item>* equipment);

	static ItemOpt item_options_selector(const SharedPtr<Item> item);

	static int equip_from_inv_selector(BodyPart bodyPartToEquip, const std::vector<SharedPtr<Item>>* inventory);

	static void show_item_info(const SharedPtr<Item> item);

};

