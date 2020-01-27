#pragma once

// User Interface class


#include "MyText.h"

#include "Item.h"
#include "Character.h"




class UI
{
private:	
	typedef std::pair<std::string, sf::Color> strCol;
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;


	inline static bool initialized = false; 

	inline static sf::RenderWindow* window;
	inline static Character* player;
	
	inline static sf::RectangleShape blackWin;
	inline static sf::RectangleShape smallBlackWin;
	inline static sf::RectangleShape fullBlackWin;
	inline static sf::RectangleShape bodyPartBlackWin;
	inline static sf::RectangleShape tickBox;



	inline static sf::Text *text;

	inline static MyText myText;



	inline static MyText invTitle = MyText();


	static void init_texts();


public:
	UI() = delete;

	
	static int center_text_posX(sf::Text text, int centeringLength = WIN_LENGTH);
	static int center_text_posX(MyText text, int centeringLength = WIN_LENGTH);
	static int center_text_posY(sf::Text text, int centeringHeight = WIN_HEIGHT);

	static void init_UI(sf::RenderWindow* win, Character* playerChar);

	static std::vector<SharedPtr<Item>> pick_items_window(std::vector<SharedPtr<Item>>* itemToChoose);

	static void player_inventory_window();

	static void item_options_window(SharedPtr<Item> item);

	static BodyPart pick_bodyPart(BodyPart bodypart);


};

