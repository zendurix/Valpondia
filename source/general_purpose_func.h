#pragma once


#include "CONFIGURATION.h"
#include "Place.h"
#include "FieldOfView.h"




enum inputType {any, space};

std::ostream & operator << (std::ostream &stream, const sf::String& sfStr);

int get_char_length(sf::Text text);
int get_char_height(sf::Text text);


double distance_meter(Place& p1, Place& p2);
double distance_meter(Character& c1, Character& c2);
double distance_meter(Character& c1, Place& p2);

bool are_same_float(float a, float b);

void sleep_for_milliseconds(int milliseconds);

void wait_for_input(inputType input);

sf::Text* init_text(int size = CHAR_SIZE);

char user_input_key();




template <typename T>
T vector_pop(std::vector<T> &vec, int pos = -1)
{
	if (pos == -1) pos = vec.size() - 1;
	T ret = vec.at(pos);
	vec.erase(vec.begin() + pos);
	return ret;
}

template <typename T>
T vector_pop(std::vector<T> &vec, T elem)
{
	int pos = std::find(vec.begin(), vec.end(), elem);
	T ret = vec.at(pos);
	vec.erase(vec.begin() + pos);
	return ret;
}



