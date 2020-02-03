#pragma once


#include "CONFIGURATION.h"
#include "Place.h"





std::ostream & operator << (std::ostream &stream, const sf::String& sfStr);

int get_char_length(sf::Text text);
int get_char_height(sf::Text text);


double distance_meter(Place& p1, Place& p2);
double distance_meter(Character& c1, Character& c2);
double distance_meter(Character& c1, Place& p2);

bool are_same_float(float a, float b);

void sleep_for_milliseconds(int milliseconds);

sf::Text* init_text(int size = CHAR_SIZE);






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



template <typename T>
std::vector<T> get_vect_items_from_indexes(std::vector<T> &vec, std::vector<int> indexes)
{
	std::vector<T> ret;
	for (int i : indexes)
		ret.push_back(vec.at(i));
	return ret;
}

