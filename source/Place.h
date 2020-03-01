#pragma once

#include "CONFIGURATION.h"
#include "ECS/ECS_Coordinator.h"

class Room;


struct Connector // MCHANGE
{
	int destinationY;
	int destinationX;
	int destinationLevel;
	char pushToGo;
	bool starisDown = false;
	bool stairsUp = false;

	inline bool operator == (const Connector& other)
	{
		if (destinationY == other.destinationY && destinationX == other.destinationX &&
			destinationLevel == other.destinationLevel && pushToGo == other.pushToGo)
			return true;
		return false;
	}
	inline bool operator != (const Connector& other)
	{
		return !(*this == other);
	}
};

class Place
{
private:
	inline static std::vector <sf::Sprite>* texturesPtr;
	inline static std::vector <sf::Sprite>* texturesASCIIPtr;


	inline static SharedPtr<ECS> ecsPtr;
	inline static SharedPtr<sf::Sprite> DEFAULT_FLOOR;

	inline static short countX = 0;
	inline static short countY = 0;


	short x, y;
	short levelID;

	//bool wasCheck,
	bool visible;
		// wasVisible,
	bool wasSeen;

	Connector connector;

	Entity entityCharHere;
	Entity obstacleHere;

	SharedPtr<Room> roomHere;

	std::vector<Entity> itemsHere;
	
//private end

public:
	inline static Connector NULLConnector = Connector{ -1, -1, -1, 'x', false, false };

	static void RESET_counters();

	inline static void set_ecsRef(SharedPtr<ECS> ecs) { ecsPtr = ecs; }
	inline static void set_def_floor_sprite(SharedPtr<sf::Sprite> floor) { DEFAULT_FLOOR = floor; }	
	inline static void set_textures(std::vector <sf::Sprite>* _textures, std::vector <sf::Sprite>* _texturesASCII)
	{
		texturesPtr = _textures; texturesASCIIPtr = _texturesASCII;
		LOG("TEXTURES IN Place class SET")
	}


	Place(short level);
	~Place();
	void RESET();
	void update_sprite();

	SharedPtr<sf::Sprite> get_sprite_to_print();
	void go_here(Entity character);
	void leave_here();
	void make_obstacle(ObstacleType type);
	void unmake_obstacle();
	void make_wall(); // MCHANGE
	void make_visible();
	void unmake_visible();
	//void drop_here(SharedPtr<Item> item);
	//void pick_up(SharedPtr<Item> item);


	inline bool is_in_room() const { return (roomHere != nullptr); }


	//getters:
	inline bool get_isObstacle()	const { return (obstacleHere == MAX_ENTITIES) ? false : true; }
	inline short get_x()			const { return x; }
	inline short get_y()			const { return y; }
	inline short get_levelID()		const { return levelID; }
	inline bool get_visible()		const { return visible; }
	inline bool get_wasSeen()		const { return wasSeen; }
	inline SharedPtr<Room> get_roomHere()	const { return roomHere; }
	inline Entity get_entityCharHere()		const { return entityCharHere; }
	//bool get_wasCheck()		const { return wasCheck; }
	//bool get_wasVisible()	const { return wasVisible; }



	inline Connector& get_connector()		{ return connector; }

	//std::vector<SharedPtr<Item>>* get_itemsHere_ptr() { return &itemsHere; }

	//setters
	//void set_wasCheck(bool set)				{ wasCheck = set; }
	//void set_wasVisible(bool set)			{ wasVisible = set; }
	inline void set_roomHere(SharedPtr<Room> set)  { roomHere = set; }
	inline void set_connector(Connector set)		{ connector = set; }

//public end
};



