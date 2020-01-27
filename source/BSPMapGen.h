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

#include "general_purpose_func.h"
#include "Node.h"
#include "Room.h"

class Place;
class Room;
class Node;

class BspMapGen
{
private:
	int treeHeight;
	Vector2D<SharedPtr<Place>> &fieldRef;
	std::vector<UniquePtr<Node>> nodes;

	BspMapGen(Vector2D<SharedPtr<Place>> &field, int height);
	~BspMapGen();
	void RESET_NodeClass();
	void RESET_field();
	void color_map_white();



	void split_map();

	bool split_node(SharedPtr<Place> parentField, std::unique_ptr<Node> &parent, int level); //ret false if error
	void split_horizontal(std::unique_ptr<Node> &parent, int& y, int& length1, int& length2, int& height1, int& height2);
	void split_vertical(std::unique_ptr<Node> &parent, int& x, int& length1, int& length2, int& height1, int& height2);

	void fill_leaves_with_rooms(std::vector <SharedPtr <Room>> *rooms);
	SharedPtr<Room> make_random_room_in_node(int nodeIndex);

	void connect_all_rooms();

	void connect_2_rooms(SharedPtr<Place> searcher1, SharedPtr<Place>  searcher2);

	void chceck_sizes(int levelmax, int MIN_SIZE);

	

public:

	static std::vector<SharedPtr<Room>> make_dung_map_ret_rooms(Vector2D<SharedPtr<Place>> &field, int treeHeight);






};

