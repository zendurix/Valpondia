#include "pch.h"
#include "general_purpose_func.h"


const float EPSILON = ACCURACY / 10.0f;


int get_char_length(sf::Text text)
{
	text.setString("A");
	return text.getLocalBounds().width;
}
int get_char_height(sf::Text text)
{
	text.setString("A");
	return text.getLocalBounds().height;
}



std::ostream & operator << (std::ostream &stream, const sf::String& sfStr)
{
	stream << sfStr.getData();
	return stream;
}


double distance_meter(Place& p1, Place& p2)
{
	return sqrt(pow(p2.get_x() - p1.get_x(), 2.0) + pow(p2.get_y() - p1.get_y(), 2.0));
}
double distance_meter(Character& c1, Character& c2)
{
	return sqrt(pow(c2.get_y() - c1.get_x(), 2.0) + pow(c2.get_y() - c1.get_y(), 2.0));
}
double distance_meter(Character& c1, Place& p2)
{
	return sqrt(pow(p2.get_x() - c1.get_x(), 2.0) + pow(p2.get_y() - c1.get_y(), 2.0));
}

bool are_same_float(float a, float b)
{
	return fabs(a - b) < EPSILON;
}

void sleep_for_milliseconds(int milliseconds)
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

sf::Text* init_text(int size)
{
	sf::Text* text = new sf::Text;
	LOG_NEW;
	sf::Font* font = new sf::Font;
	LOG_NEW;
	font->loadFromFile("../res/fonts/DOSfont.ttf");
	text->setFont(*font);
	text->setCharacterSize(size);
	text->setFillColor(sf::Color::White);
	return text;
}