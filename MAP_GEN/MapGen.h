#pragma once

#include "../pch.h"


class GAME;
class Level;


class MapGen
{
protected:
	inline MapGen() {};

	inline static  GAME* gamePtr;
	Level* levelPtr;



public:

	inline static void set_gamepTr(GAME* g) { gamePtr = g; }

	//inline void set_levelRef(Level& level) { levelRef = level; }


};

