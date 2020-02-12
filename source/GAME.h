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
class MENU;

class GAME
{
	friend class GAME_Printer;
	friend class GAME_charControler;

	friend int main(); // temporary
	friend class MENU; // tempoorary
	friend bool MENU_handler_ret_startGame(GAME* game, MENU menu, bool* exit);	 // temporary
	friend void MENU_DEBUG_handler(GAME* game, MENU menu);						 // tempoorary



private:
	static GAME* instance;
	GAME();
	~GAME();

	void init_components();	

	sf::RenderWindow* windowHandle;

	CharacterPlayer* player;
	Vector2D<SharedPtr<CharacterEnemy>> enemiesByLevels;

	std::vector <Level*> levels;
	Level* levelActive;
	int levelActiveId;


public:	
	static GAME* getInstance();
	static void DELETEinstance();

	// COMPONENTS:
	GAME_Printer* Printer;
	GAME_charControler* CharControler;


	
	void setWindow(sf::RenderWindow* windowPtr);
	void make_all_levels();
	void RESET_levels();
	void unmake_visible_whole_level();

	void make_level(Connector connector);



	void reset_visibility(Character character);
	template<typename... Args>
	void reset_visibility(Character character, Args... args) // recursive variadic function
	{
		reset_visibility(character);
		reset_visibility(args...);
	}



};

