#pragma once 
// Node of BSP tree in BSPMapGen

#include "CONFIGURATION.h"
#include "Place.h"
#include "Room.h"

class Place;
class Room;

class Node
{
public:
	static int level;
	static int nodeCount;
	int nodeIndex;
	int levelIndex;

	Node* parent;
	Node* sister;
	Node* childreen[2];

	std::vector <int> family;

	std::shared_ptr<Place> fieldNode; // pointer to first element of node field

	std::shared_ptr <Room> room;

	int length;
	int height;

	bool horizontal; // if false, than vertical

	bool isRoot; // first node of tree (no parent)
	bool isLeaf; // node in last tree level (no childreen)


	Node(int levelmax, std::shared_ptr<Place> fieldNode1, int length1, int height1, int orientation);
	~Node();

	void check_family();
	void give_room_number();
	sf::String make_family_list();

};


void make_children(std::unique_ptr<Node> &sister1, std::unique_ptr<Node> &sister2,
				   std::unique_ptr<Node> &parent1);
