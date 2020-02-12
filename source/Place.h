#pragma once

#include "CONFIGURATION.h"
#include "Character.h"
#include "Room.h"
#include "colors.h"
#include "Item.h"
#include "ItemComp.h"


class Room;

struct Connector
{
	SharedPtr<Place> destination = nullptr;
	char pushToGo;
	int levelDestination = -1;
};

class Place
{
private:
	static short countX, countY;
	short x, y;
	short levelID;

	unsigned char printFormat;
	unsigned char prevPrintFormat;

	sf::Color tileColor;

	bool isObstacle,
	     isInRoom,
	     isDoors,
	     isWall,
	     wasCheck,
	     visible,
	     wasVisible,
	     wasSeen,
	     changedPrint,
	     stairsDown,
	     stairsUp;


	Character* characterHere;
	SharedPtr <Room> roomHere;

	std::vector< SharedPtr<Item> > itemsHere;

	
//private end

public:
	Connector connector;




	Place(short level);
	~Place();

	static void RESET_counters();
	void go_here(Character* character);
	void leave_here();
	void RESET();	
	void make_obstacle();
	void unmake_obstacle();
	void make_wall();
	void make_visible();
	void unmake_visible();
	void drop_here(SharedPtr<Item> item);
	void pick_up(SharedPtr<Item> item);
	   	 

	//getters:
	short get_x()			{ return x; }
	short get_y()			{ return y; }
	short get_levelID()		{ return levelID; }
	bool get_isObstacle()	{ return isObstacle; }
	bool get_isInRoom()		{ return isInRoom; }
	bool get_isDoors()		{ return isDoors; }
	bool get_isWall()		{ return isWall; }
	bool get_wasCheck()		{ return wasCheck; }
	bool get_visible()		{ return visible; }
	bool get_wasVisible()	{ return wasVisible; }
	bool get_wasSeen()		{ return wasSeen; }
	bool get_changedPrint()	{ return changedPrint; }
	bool get_stairsDown()	{ return stairsDown; }
	bool get_stairsUp()		{ return stairsUp; }
	unsigned char get_printFormat()			 { return printFormat; }
	unsigned char get_prevPrintFormat()		 { return prevPrintFormat; }
	SharedPtr <Room> get_roomHere()	 { return roomHere; }
	sf::Color get_tileColor()				 { return tileColor; }
	Character* get_characterHere()			 { return characterHere; }
	std::vector<SharedPtr<Item>>* get_itemsHere_ptr() { return &itemsHere; }

	//setters
	void set_isInRoom(bool set)				     { isInRoom = set; }
	void set_isDoors(bool set)				     { isDoors = set; }
	void set_wasCheck(bool set)				     { wasCheck = set; }
	void set_stairsDown(bool set)			     { stairsDown = set; }
	void set_stairsUp(bool set)				     { stairsUp = set; }
	void set_changedPrint(bool set)			     { changedPrint = set; }
	void set_wasVisible(bool set)			     { wasVisible = set; }
	void set_tileColor(sf::Color set)			 { tileColor = set; }
	void set_printFormat(unsigned char set)		 { printFormat = set; }
	void set_prevPrintFormat(unsigned char set)  { prevPrintFormat = set; }
	void set_roomHere(SharedPtr<Room> set) { roomHere = set; }

//public end

};



