#pragma once

#include "CONFIGURATION.h"
#include "general_purpose_func.h"


enum class inputType { any, space };

class Input
{
private:
	inline static sf::RenderWindow* winPtr;

public:
	Input() = delete;
	static void init_Input(sf::RenderWindow* window) 
	{ 
		winPtr = window;
		LOG("Input..............................initialized");
	}

	static char user_input_key();
	static	void wait_for_input(inputType input);
};

