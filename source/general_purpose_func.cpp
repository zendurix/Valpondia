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


void wait_for_input(inputType input)
{
	GAME* game = GAME::getInstance();
	sf::Event evnt;
	bool wait = true;
	while (wait)
	{
		game->windowHandle->pollEvent(evnt);
		if (evnt.type == sf::Event::KeyPressed)
			if (input == space)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
					wait = false;
	}
	sleep_for_milliseconds(100);
}

sf::Text* init_text(int size)
{
	sf::Text* text = new sf::Text;
	LOG_NEW;
	sf::Font* font = new sf::Font;
	LOG_NEW;
	font->loadFromFile("../SFML/sources/DOSfont.ttf");
	text->setFont(*font);
	text->setCharacterSize(size);
	text->setFillColor(sf::Color::White);
	return text;
}

char user_input_key()
{ 

	GAME* game = GAME::getInstance();
	char input = '\0';
	while (game->windowHandle->isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) return ' ';
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) return '\n';
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) return '\t';

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) return '1';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad1)) return '1';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) return '2';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2)) return '2';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) return '3';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad3)) return '3';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) return '4';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4)) return '4';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) return '5';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5)) return '5';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) return '6';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6)) return '6';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) return '7';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7)) return '7';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) return '8';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8)) return '8';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) return '9';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9)) return '9';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) return '0';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0)) return '0';
			
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add)) return '+';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract)) return '-';
									
		/////////					
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) return '8';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) return '2';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) return '4';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) return '6';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) return '7';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) return '9';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) return '1';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) return '3';
		////////					
									
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U) &&
				 sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))	return 'U';	
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	return 'd';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))	return 'D';

	

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) return 'p';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) return 'i';


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			int a = 2;

			return STD_ESC;
		}

	
	}
	return '\\';
}
