#include "pch.h"
#include "MyText.h"

#include "general_purpose_func.h"

std::string MyText::get_string() const
{
	std::string ret = "";
	for (int i = 0; i < texts.size(); i++)
	{
		ret += texts[i].first;
		if (i != texts.size()-1)
			ret += " ";
	}
	return ret;
}
sf::Text MyText::get_text() const
{
	sf::Text text;
	text.setString(get_string());
	return text;
}


MyText::MyText(std::vector<strCol> textVec, int size, int x, int y, sf::Font* font)
	: texts(textVec), font(font), charSize(size)
{
	position = sf::Vector2f(x, y);

	text.setFont(*font);
	text.setCharacterSize(charSize);

	charLength = get_char_length(text);
	charHeight = get_char_height(text);
}
MyText::MyText(strCol texCol, int size, int x, int y, sf::Font* font)
	: font(font), charSize(size)
{
	texts.push_back(texCol);
	position = sf::Vector2f(x, y);

	text.setFont(*font);
	text.setCharacterSize(size);

	charLength = get_char_length(text);
	charHeight = get_char_height(text);
}
MyText::MyText() 
{	// call first to init STD_FONT
	if (STD_FONT == nullptr)
	{
		LOG_NEW;
		STD_FONT = new sf::Font;
		STD_FONT->loadFromFile("../res/fonts/DOSfont.ttf");
		LOG("MyText STD_FONT....................loaded");
	}
}
MyText::MyText(const MyText& copy)
{
	texts = copy.get_texts();
	font = STD_FONT;
	text.setFont(*font);
	charSize = CHAR_SIZE; // copy.getPosition_charSize();
	text.setCharacterSize(charSize);

	charLength = get_char_length(text);
	charHeight = get_char_height(text);
}


MyText::~MyText()
{
}





MyText& MyText::operator + (const strCol& addText)
{
	texts.push_back(addText);
	return *this;
}
void MyText::operator += (const strCol& addText)
{
	*this = *this + addText;
}	
MyText& MyText::operator + (const MyText& addText)
{
	MyTextVext vec = addText.get_texts();
	for (strCol elem : vec)
	{
		texts.push_back(elem);
	}
	return *this;
}
void MyText::operator   += (const MyText& addText)
{
	*this = *this + addText;
}

void MyText::window_draw(sf::RenderWindow* window)
{
	int x = position.x;
	int y = position.y;
	

	for (strCol setter : texts)
	{
		text.setString(setter.first);
		text.setFillColor(setter.second);

		text.setPosition(x, y);
		x += (charLength+4) * (setter.first.size()); // add 4 pixel - space between chars


		window->draw(text);
	}
}



void MyText::clear() 
{
	texts.clear();
}