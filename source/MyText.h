#pragma once



#include "CONFIGURATION.h"
#include "colors.h"

// multicolor string to draw on sfml window



typedef std::pair<std::string, sf::Color> strCol;


class MyText
{
private:
	typedef std::pair<std::string, sf::Color> strCol;
	typedef std::vector<strCol> MyTextVext;
	typedef sf::Color COL;


	std::vector<strCol> texts;

	sf::Text text;

	sf::Font* font;

	int charSize;
	int charLength, charHeight;

	sf::Vector2f position;

	inline static sf::Font* STD_FONT;


public:
	MyText(std::vector<strCol> textVec, int size = CHAR_SIZE, int x = 0, int y = 0, sf::Font* font = STD_FONT);
	MyText(strCol texCol, int size = CHAR_SIZE, int x = 0, int y = 0, sf::Font* font = STD_FONT);
	MyText(const MyText& copy);
	MyText();
	~MyText();



	MyText& operator + (const strCol& addText); 
	MyText& operator + (const MyText& addText);
	void operator   += (const strCol& addText);
	void operator   += (const MyText& addText);

	void window_draw(sf::RenderWindow* window);

	void clear();


	// getters 
	std::string get_string() const;
	sf::Text get_text() const;
	static sf::Font* get_STD_FONT()  { return STD_FONT; }
	sf::Vector2f getPosition() const { return position; }
	int get_charLength()	   const { return charLength; }
	int get_charHeight()	   const { return charHeight; }
	MyTextVext get_texts()	   const { return texts; }
	int getPosition_charSize() const { return charSize; }
	COL get_color_first()	   const { return texts[0].second; }
	
	// my function naming convenction (function_name()) is broken here (in setPosition)
	// in purpose of MyText being similiar to sf::Text

	// setters
	void setPosition(int xSet, int ySet)  { position.x = xSet; position.y = ySet; }
	void setPosition(sf::Vector2f posSet) { position.x = posSet.x; position.y = posSet.y; }
	void set_color_first(COL color)		  { texts[0].second = color; }
	void set_color_all(COL color) { for (strCol &x : texts) x.second = color; }

};

