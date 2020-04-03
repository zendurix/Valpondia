#pragma once

enum class Attitude
{	hostile = -1, // will attack player
	neutral = 0,  // won't attack player or help player
	friendly = 1  // will help player kill hostiles
};
enum class Behavior
{	sleeping = 0,	
	guarding,
	wandering,
	hunting
};



struct AI
{
	Attitude attitude;
	Behavior behavior;

};