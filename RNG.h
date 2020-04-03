#pragma once

#include "pch.h"


// Random Number Generator


inline thread_local std::mt19937 gen{ std::random_device{}() };

class RNG
{
public:
	RNG() = delete;


	inline static int randInt(int min, int max) // range is <min, max>
	{
		return std::uniform_int_distribution<int>{min, max}(gen);
	}


	template <typename T>
	inline static T random_from_vect(std::vector<T> vect)
	{
		int max = vect.size() - 1;
		int randNumb = RNG::randInt(0, max);
		return vect[randNumb];
	}
};
