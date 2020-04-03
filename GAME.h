#pragma once        

#include "CONFIGURATION.h"
#include "ECS/ECS_Coordinator.h"
#include "GAME_Printer.h"
#include "GAME_Factory.h"


class Level;
class ECS;
class Place;
class Connector;
class GAME_Printer;
class GAME_Factory;

class GAME
{
	friend class GAME_Printer;

private:
	inline static GAME* instance = nullptr;
	GAME();
	~GAME();
	void init();

	sf::RenderWindow* windowHandle;

	//CharacterPlayer player;
	//Vector2D<SharedPtr<CharacterEnemy>> enemiesByLevels;

	std::vector <Level*> levels;
	Level* levelActive;
	

	Entity player;

public:


	SharedPtr<ECS> ecs; // MCHANGE

	// COMPONENTS:
	GAME_Printer* Printer;
	GAME_Factory* Factory;


	static GAME* getInstance();
	static void DELETEinstance();
	void setWindow(sf::RenderWindow* windowPtr);


	Entity make_player();


	void RESET_levels();
	void unmake_visible_whole_level();
	void make_level(Connector connector, bool makeAllLevels = false);

	void reset_visibility(Entity entity);



	// getters
	inline Level* get_levelActive()					{ return levelActive; }
	inline std::vector<Level*>* get_levels()		{ return &levels; }
	SharedPtr<Place> get_place(Position pos);
};

