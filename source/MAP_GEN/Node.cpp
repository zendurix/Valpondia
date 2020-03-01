#include "pch.h"
#include "Node.h"


Node::Node(int levelmax, SharedPtr<Place> fieldNode1, int length1, int height1, int orientation)
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

	if (nodeIndex == 1 || nodeIndex == 3 ||
		nodeIndex == 7 || nodeIndex == 15 ||
		nodeIndex == 31 || nodeIndex == 63)
	{
		actualTreeLevel++;
	}
	levelIndex = actualTreeLevel;

	if (actualTreeLevel == 0)
	{
		isRoot = true;
		parent = nullptr;
		sister = nullptr;
	}
	else
	{
		isRoot = false;
	}

	if (actualTreeLevel == levelmax)
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

void Node::make_children(std::unique_ptr<Node> &child1, std::unique_ptr<Node> &child2)
{
	child1->sister = child2.get();
	child2->sister = child1.get();

	child1->parent = this;
	child2->parent = this;

	childreen[0] = child1.get();
	childreen[1] = child2.get();
}


