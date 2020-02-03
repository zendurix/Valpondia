#include "pch.h"
#include "Input.h"



void Input::wait_for_input(inputType input)
{
	sf::Event evnt;
	bool wait = true;
	while (wait)
	{
		winPtr->pollEvent(evnt);
		if (evnt.type == sf::Event::KeyPressed)
			if (input == inputType::space)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
					wait = false;
	}
	sleep_for_milliseconds(100);
}



char Input::user_input_key()
{
	char input = '\0';
	while (winPtr->isOpen())
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


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) return '8';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) return '2';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) return '4';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) return '6';

		/////////	
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) return '7';
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) return '9';
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) return '1';
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) return '3';
		////////					

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))	return 'U';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	return 'd';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))	return 'D';



		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) return 'p';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) return 'i';
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) return 'e';


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			int a = 2;

			return STD_ESC;
		}


	}
	return '\\';
}
