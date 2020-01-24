#pragma once

#include "CONFIGURATION.h"
#include "Character.h"
#include "Room.h"
#include "colors.h"
#include "Item.h"
#include "ItemComp.h"


class Room;

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
	std::shared_ptr <Room> roomHere;

	std::vector< std::shared_ptr<Item> > itemsHere;

	
//private end

public:
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
	void drop_here(std::shared_ptr<Item> item);
	void pick_up(std::shared_ptr<Item> item);
	   	 

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
	std::shared_ptr <Room> get_roomHere()	 { return roomHere; }
	sf::Color get_tileColor()				 { return tileColor; }
	Character* get_characterHere()			 { return characterHere; }
	std::vector<std::shared_ptr<Item>>* get_itemsHere_ptr() { return &itemsHere; }

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
	void set_roomHere(std::shared_ptr<Room> set) { roomHere = set; }

//public end

};

