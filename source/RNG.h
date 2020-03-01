#pragma once


// Random Number Generator

#include "pch.h"

inline thread_local std::mt19937 gen{ std::random_device{}() };
class RNG
{
public:
	RNG() = delete;
	static int randInt(int min, int max) // range is <min, max>
	{
		return std::uniform_int_distribution<int>{min, max}(gen);
	}
};
