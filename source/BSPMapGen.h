#pragma once
// random map generator, based on BSP  (Binary Space Partitioning using binary tree)
// makes FULL binary tree to given max level
/*    EXAMPLE (maxlevel == 2):
					0            LEVEL 0:  main root node
				   / \
				 /     \
			   1         2		 LEVEL 1
			  / \       / \
			 /   \     /   \
			3	  4   5     6    LEVEL 2: last level, leaves
										  amount of nodes on that level == 2^maxlevel
										  amount of leaves is amount of rooms to be placed
	// after placing them all rooms are coneccted
	// connections will be: 3=4, 5=6, and randomly (3 || 4)=(5 || 6), so all branchess will be connected
*/

#include "GAME.h"
#include "Node.h"
#include "Room.h"

class Place;
class Room;
class Node;
class GAME;

class BspMapGen
{
private:
	GAME* game;
	int nodesNum;
	std::unique_ptr<Node> root_node;
	bool testing;
	std::vector<std::unique_ptr<Node>> nodes;

	BspMapGen(bool test);
	~BspMapGen();

	void make_full_tree();

	bool split_dungeon_BSP(SharedPtr<Place>  field, std::unique_ptr<Node> &parent, int level);

	void fill_leaves_with_rooms(std::vector <SharedPtr <Room>> *rooms);

	void connect_all_rooms();

	void connect_2_rooms(SharedPtr<Place> searcher1, SharedPtr<Place>  searcher2);

	void chceck_sizes(int levelmax, int MIN_SIZE);

public:
	static std::vector<SharedPtr<Room>> make_dung_map_ret_rooms(Vector2D<SharedPtr<Place>> &field, bool test);


};

