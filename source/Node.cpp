#include "pch.h"
#include "Node.h"

int Node::level = 0;
int Node::nodeCount = -1;

Node::Node(int levelmax, std::shared_ptr<Place> fieldNode1, int length1, int height1, int orientation)
{
	fieldNode = fieldNode1;
	//fieldNode->set_printFormat('X');
	length = length1;
	height = height1;

	horizontal = orientation;

	sister = nullptr;
	room = nullptr;

	nodeCount++;
	nodeIndex = nodeCount;

	if (nodeIndex == 1  || nodeIndex == 3  ||
		nodeIndex == 7  || nodeIndex == 15 ||
		nodeIndex == 31 || nodeIndex == 63)
	{
		level++;
	}
	levelIndex = level;

	if (level == 0)
	{
		isRoot = true;
		parent = nullptr;
		sister = nullptr;
	}
	else
	{
		isRoot = false;
	}

	if (level == levelmax)
	{
		isLeaf = true;
		childreen[0] = nullptr;
		childreen[1] = nullptr;
	}
	else
	{
		isLeaf = false;
	}
}

Node::~Node() 
{
	parent = nullptr;
	sister = nullptr;		
	childreen[0] = nullptr;
	childreen[1] = nullptr;
}


// lists all "parents and grandparents" of node, in family vector
void Node::check_family()
{
	Node* familySearcher = parent;
	while (familySearcher != nullptr)
	{
		family.push_back(familySearcher->nodeIndex);
		familySearcher = familySearcher->parent;
	}
}

void Node::give_room_number()
{
	room->roomIndex = nodeIndex;
}

sf::String Node::make_family_list()
{
	sf::String str = "";
	for (int x : family)
	{
		str += std::to_string(x);
		if (x != 0)
			str += ".";
	}
	return str;
}

void make_children(std::unique_ptr<Node> &sister1, std::unique_ptr<Node> &sister2,
				   std::unique_ptr<Node> &parent1)
{
	sister1->sister = sister2.get();
	sister2->sister = sister1.get();

	sister1->parent = parent1.get();
	sister2->parent = parent1.get();

	parent1->childreen[0] = sister1.get();
	parent1->childreen[1] = sister2.get();
}


