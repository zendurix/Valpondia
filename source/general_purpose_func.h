#pragma once

#include "CONFIGURATION.h"


class Place;


const float EPSILON = ACCURACY / 10.0f;


std::ostream & operator << (std::ostream &stream, const sf::String& sfStr);

int get_char_length(sf::Text text);
int get_char_height(sf::Text text);


double distance_meter(const Place& p1, const Place& p2);
// double distance_meter(const Character& c1, const Character& c2);
// double distance_meter(const Character& c1, const Place& p2);

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

template <typename T>
T random_from_vect(std::vector<T> vect)
{
	int max = vect.size() - 1;
	int randNumb = RNG::randInt(0, max);
	return vect[randNumb];
}


template <typename T>
bool vector_contains(std::vector<T> &vec, T elem)
{
	return (std::find(vec.begin(), vec.end(), elem) != vec.end());
}