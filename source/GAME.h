#pragma once        // this class is singleton (only one object)


#include "CONFIGURATION.h"
#include "CharacterPlayer.h"
#include "CharacterEnemy.h"
#include "Character.h"
#include "FieldOfView.h"
#include "Level.h"

#include "GAME_Printer.h"
#include "GAME_charControler.h"


class Level; 
class Node;
class GAME_Printer;
class GAME_charControler;

class GAME
{
private:
	static GAME* instance;
	GAME();
	~GAME();

	void init_components();


public:	
	static GAME* getInstance();
	static void DELETEinstance();

	// COMPONENTS:
	GAME_Printer* Printer;
	GAME_charControler* CharControler;

	sf::RenderWindow* windowHandle;	

	CharacterPlayer* player;

	std::vector <Level*> levels;
	Level* levelActive;
	short levelActiveId;
	
	void setWindow(sf::RenderWindow* windowPtr);
	void make_new_level(enum lvType levelType);
	void RESET_levels();
	void unmake_visible_whole_level();



	void reset_visibility(Character character);
	template<typename... Args>
	void reset_visibility(Character character, Args... args) // recursive variadic function
	{
		reset_visibility(character);
		reset_visibility(args...);
	}
};

