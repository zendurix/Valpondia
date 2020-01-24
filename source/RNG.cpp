#include "pch.h"
#include "RNG.h"

thread_local std::mt19937 gen{ std::random_device{}() };

int random(int min, int max) // range is <min, max>
{
	return std::uniform_int_distribution<int>{min, max}(gen);
}
