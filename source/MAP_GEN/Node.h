#pragma once 
// Node of BSP tree in BSPMapGen

#include "CONFIGURATION.h"
#include "Place.h"
#include "Room.h"

class Place;
class Room;

class Node
{
friend class BspMapGen;
public: 
	Node(int levelmax, SharedPtr<Place> fieldNode1, int length1, int height1, int orientation);
	~Node();
private:
	inline static int actualTreeLevel = 0;
	inline static int nodeCount = -1;
	int nodeIndex;
	int levelIndex;

	Node* parent;
	Node* sister;
	Node* childreen[2];

	std::vector <int> family;

	SharedPtr<Place> fieldNode; // pointer to first element of node field

	SharedPtr <Room> room;

	int length;
	int height;

	bool horizontal; // if false, than vertical

	bool isRoot; // first node of tree (no parent)
	bool isLeaf; // node in last tree level (no childreen)




	void check_family();
	void give_room_number();
	sf::String make_family_list();


	void make_children(std::unique_ptr<Node> &child1, std::unique_ptr<Node> &child2);



	// getters
	inline static int get_actualTreeLevel()  { return actualTreeLevel; }
	inline bool get_isLeaf()				const { return isLeaf; }


	// setters
	inline static void set_actualTreeLevel(int set) { actualTreeLevel = set; }
};


