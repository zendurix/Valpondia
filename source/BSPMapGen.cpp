#include "pch.h"
#include "BspMapGen.h"


std::vector<SharedPtr<Room>> BspMapGen::make_dung_map_ret_rooms(Vector2D<SharedPtr<Place>> &fieldRef, int treeHeight)
{
	BspMapGen tree(fieldRef, treeHeight);
	std::vector<SharedPtr<Room>> rooms;
	
	int restartCount = 0;
	bool restart = false;
	while (!restart)
	{
		try
		{
			tree.split_map();
			restart = true;
		}
		catch (...)
		{
			restart = false;
			restartCount++;
			tree.RESET_field();
		}
	}
	LOG("BSP tree restart count: " << restartCount);

	make_whole_map_obstacle(fieldRef);
	tree.fill_leaves_with_rooms(&rooms);
	tree.connect_all_rooms();

	// TEST
	//#include "GAME.h"
	//GAME::getInstance()->Printer->print_field();

	return rooms;
}



BspMapGen::BspMapGen(Vector2D<SharedPtr<Place>> &field, int height)
	: fieldRef(field), treeHeight(height)
{
}

BspMapGen::~BspMapGen()
{
	RESET_NodeClass();
}

void BspMapGen::RESET_NodeClass()
{
	nodes.clear();
	Node::nodeCount = -1;
	Node::set_actualTreeLevel(0);
}

void BspMapGen::RESET_field()
{
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
			fieldRef[i][j]->RESET();
}

void BspMapGen::color_map_white()
{ // used in testing
	for (int i = 0; i < MYHEIGHT; i++)
		for (int j = 0; j < MYLENGTH; j++)
			fieldRef[i][j]->set_tileColor(sf::Color::White);
}


void BspMapGen::split_map()
{
	int actualLevel;

	UniquePtr<Node> rootNode = std::make_unique<Node>(treeHeight, fieldRef[0][0], MYLENGTH, MYHEIGHT, 0);
	nodes.push_back(std::move(rootNode));

	for (int i = 0; i < treeHeight; i++)
	{
		actualLevel = Node::get_actualTreeLevel();

		int startingNodeId = (int)pow(2, actualLevel) - 1;
		int endingNodeId = (int)pow(2, actualLevel + 1) - 2;

		for (int j = startingNodeId; j <= endingNodeId; j++)
		{
			bool splitSuccesful = split_node(nodes[j]->fieldNode, nodes[j], actualLevel);
			if (!splitSuccesful)
			{ // RNG failed (loops over 200 times)
				RESET_NodeClass();
				throw "ERROR"; 
			}
		}
	}
}







bool BspMapGen::split_node(SharedPtr<Place> parentField, std::unique_ptr<Node> &parent, int level)
{ 
	UniquePtr<Node> nodeChild1, nodeChild2;
	bool vertical = random(0, 1);
	int length1, length2, height1, height2;
	int x, y;
	int errorCount = 0;


	if (vertical)  // vertical
	{
		do
		{
			split_vertical(parent, x, length1, length2, height1, height2);
			errorCount++;
			if (errorCount > 200)
				return false;

		} while (length1 < MIN_ROOM_SIZE + PLACE_FOR_WALLS || length2 < MIN_ROOM_SIZE + PLACE_FOR_WALLS);
	}
	else // (!vertical) -> horizontal
	{
		do
		{
			split_horizontal(parent, x, length1, length2, height1, height2);
			errorCount++;
			if (errorCount > 200)
				return false;
		} while (height1 < MIN_ROOM_SIZE + PLACE_FOR_WALLS || height2 < MIN_ROOM_SIZE + PLACE_FOR_WALLS);
	}

	nodeChild1 = std::make_unique<Node>(treeHeight, parentField, length1, height1, vertical);

	int fieldX = parentField->get_x();
	int fieldY = parentField->get_y();
	
	if (vertical)	fieldX += length1;
	else 			fieldY += height1;
	fieldY = (fieldY == MYHEIGHT) ? fieldY - 1 : fieldY;

	parentField = fieldRef[fieldY][fieldX];

	nodeChild2 = std::make_unique<Node>(treeHeight, parentField, length2, height2, vertical);

	parent->make_children(nodeChild1, nodeChild2);
	nodes.push_back(std::move(nodeChild1));
	nodes.push_back(std::move(nodeChild2));
	return true;
}

void BspMapGen::split_horizontal(std::unique_ptr<Node> &parent, int& y, int& length1, int& length2, int& height1, int& height2)
{
	int minY = parent->fieldNode->get_y() + parent->height / 2 - MIN_ROOM_SIZE / 2;
	int maxY = parent->fieldNode->get_y() + parent->height / 2 + MIN_ROOM_SIZE / 2;
	y = random(minY, maxY);
	length1 = parent->length;
	length2 = length1;
	height1 = y - parent->fieldNode->get_y();
	height2 = parent->height - height1;
}

void BspMapGen::split_vertical(std::unique_ptr<Node> &parent, int& x, int& length1, int& length2, int& height1, int& height2)
{
	int minX = parent->fieldNode->get_x() + parent->length / 2 - MIN_ROOM_SIZE / 2;
	int maxX = parent->fieldNode->get_x() + parent->length / 2 - MIN_ROOM_SIZE / 2;
	x = random(minX, maxX);
	length1 = x - parent->fieldNode->get_x();
	length2 = parent->length - length1;
	height1 = parent->height;
	height2 = parent->height;
}










void BspMapGen::fill_leaves_with_rooms(std::vector <SharedPtr <Room>> *rooms)
{
	SharedPtr<Room> room;
	int nodesSize = nodes.size();

	for (int i = 0; i < nodesSize; i++)
	{
		if (nodes[i]->get_isLeaf())
		{
			room = make_random_room_in_node(i);
			rooms->push_back(room);
		}
	}
	for (int i = 0; i < nodesSize; i++)
	{
		if (nodes[i]->isLeaf)
			nodes[i]->check_family();
	}

}

SharedPtr<Room> BspMapGen::make_random_room_in_node(int nodeIndex)
{
	int length, height;
	int x, y;
	SharedPtr <Room> room;

	int maxLength = nodes[nodeIndex]->length - PLACE_FOR_WALLS;
	int maxHeight = nodes[nodeIndex]->height - PLACE_FOR_WALLS;

	//do
	{
		length = random(MIN_ROOM_SIZE, maxLength);
		height = random(MIN_ROOM_SIZE, maxHeight);
	}// while ((double)height / length < ROOM_WALLS_PROPORTION ||	(double)length / height < ROOM_WALLS_PROPORTION);
	
	int parentX = nodes[nodeIndex]->fieldNode->get_x();
	int parentY = nodes[nodeIndex]->fieldNode->get_y();

	int maxX = (parentX + nodes[nodeIndex]->length) - (length + PLACE_FOR_WALLS);
	int maxY = (parentY + nodes[nodeIndex]->height) - (height + PLACE_FOR_WALLS);

	if (parentX + PLACE_FOR_WALLS < maxX)	x = random(parentX, maxX);
	else									x = parentX;

	if (parentY + PLACE_FOR_WALLS < maxY)	y = random(parentY, maxY);
	else									y = parentY;

	room = std::make_shared<Room>();
	make_room(fieldRef, x, y, length, height, room);
	nodes[nodeIndex]->room = room;
	return room;
}




void BspMapGen::connect_all_rooms()
{
	SharedPtr<Place> searcher1 = nullptr, searcher2 = nullptr;
	Node* node1 = nullptr, *node2 = nullptr;
	bool horizontalConnection;
	bool foundRoute = false;
	int childSelect;	
	int addConnections = 3, aditionalConnectionsCounter = 0; // to add more connections on first level of the tree

	for (int treeLevel = treeHeight; treeLevel > 0; treeLevel--)
	{
		int startNodeIndex = (int)pow(2, treeLevel) - 1;
		int maxNodeIndex = (int)pow(2, treeLevel + 1) - 2;
		auto iAdder = [&]() { return (treeLevel != 1) ? 2 : ((aditionalConnectionsCounter < addConnections) ? 0 : 2); };

		for (int i = startNodeIndex; i < maxNodeIndex;	i += iAdder())
		{
			aditionalConnectionsCounter += (treeLevel == 1) ? 1 : 0;
			foundRoute = false;	
			while (!foundRoute)
			{
				node1 = nodes[i].get();
				node2 = nodes[i + 1].get();
				while (node1->childreen[0] != nullptr)
				{
					childSelect = random(0, 1);
					node1 = node1->childreen[childSelect];
					node2 = node2->childreen[childSelect];
				}

				if (nodes[i]->horizontal)
				{
					if (node2->room->cornerNW.x >= node1->room->cornerNE.x)
						foundRoute = true;
				}
				else  // vertical
				{
					if (node2->room->cornerNE.y >= node1->room->cornerSE.y)
						foundRoute = true;
				}
			}

			horizontalConnection = (node2->room->cornerNE.y - node1->room->cornerSE.y >=
				node2->room->cornerNW.x - node1->room->cornerNE.x) ? 0 : 1;

			int doorPosY1 = random(node1->room->cornerNE.y + 2, node1->room->cornerNE.y + 2 + (node1->room->height - 2));
			int doorPosY2 = random(node2->room->cornerNE.y + 2, node2->room->cornerNE.y + 2 + (node2->room->height - 2));
			int doorPosX1 = random(node1->room->cornerSW.x + 2, node1->room->cornerSW.x + 2 + (node1->room->length - 2));
			int doorPosX2 = random(node2->room->cornerNW.x + 2, node2->room->cornerNW.x + 2 + (node2->room->length - 2));

			if (horizontalConnection) //(nodes[i]->horizontal)
			{
				searcher1 = fieldRef[doorPosY1][node1->room->cornerNE.x];
				searcher2 = fieldRef[doorPosY2][node2->room->cornerNW.x];
			}													  
			else // vertical									  
			{													  
				searcher1 = fieldRef[node1->room->cornerSW.y][doorPosX1];
				searcher2 = fieldRef[node2->room->cornerNW.y][doorPosX2];
			}

			connect_2_rooms(searcher1, searcher2); 
		}
	}
}

void BspMapGen::connect_2_rooms(SharedPtr<Place> searcher1, SharedPtr<Place>  searcher2)
{
	searcher1->unmake_obstacle();
	SharedPtr<Place> bestDir = searcher1;
	SharedPtr<Place> searcher1START = searcher1;
	SharedPtr<Place> placeHolder = nullptr;
	int errorCounter = 0;
	double bestDist;
	bool bestFound = false;
	bool ignoreIsWall = false;

	//if searcher is on edge of map place it on different corner of room
	if (searcher1->get_x() == 0 || searcher1->get_y() == 0)
		searcher1 = fieldRef[searcher1->get_roomHere()->cornerSE.y][searcher1->get_roomHere()->cornerSE.x - 1];
	if (searcher1->get_x() == MYLENGTH - 1 || searcher1->get_y() == MYHEIGHT - 1)
		searcher1 = fieldRef[searcher1->get_roomHere()->cornerNW.y][searcher1->get_roomHere()->cornerNW.x + 1];

	searcher1->unmake_obstacle();
	
	// check if searcher isn't going out of the map. macros are used to save space and visibility of code
	#define CHECKbth CHECKmin if CHECKmax
	#define CHECKmin (searcher1->get_x() != 0 && searcher1->get_y() != 0)
	#define CHECKmax (searcher1->get_x() != MYLENGTH - 1 && searcher1->get_y() != MYHEIGHT - 1)

	while (searcher1 != searcher2)
	{
		bestDist = 10000000.0;
		bestFound = false;

		for (int i = 1; i < 10; i++)
		{
			placeHolder = searcher1;
			switch (i)
			{
				case 1:	if CHECKbth searcher1 = fieldRef[searcher1->get_y() + 1][searcher1->get_x() - 1];	break;
				case 2:	if CHECKmax searcher1 = fieldRef[searcher1->get_y() + 1][searcher1->get_x()    ];	break;
				case 3:	if CHECKmax searcher1 = fieldRef[searcher1->get_y() + 1][searcher1->get_x() + 1];	break;
				case 4:	if CHECKmin searcher1 = fieldRef[searcher1->get_y()    ][searcher1->get_x() - 1];	break;
				case 5:	continue;																			break;
				case 6:	if CHECKmax searcher1 = fieldRef[searcher1->get_y()    ][searcher1->get_x() + 1];	break;
				case 7:	if CHECKmin searcher1 = fieldRef[searcher1->get_y() - 1][searcher1->get_x() - 1];	break;
				case 8:	if CHECKmin searcher1 = fieldRef[searcher1->get_y() - 1][searcher1->get_x()    ];	break;
				case 9:	if CHECKbth searcher1 = fieldRef[searcher1->get_y() - 1][searcher1->get_x() + 1];	break;
			}

			if (ignoreIsWall || !searcher1->get_isWall() || searcher1 == searcher2)   
			{
				if (distance_meter(*searcher1, *searcher2) < bestDist)
				{
					int bbb = 4;
					bestDir = searcher1;
					bestDist = distance_meter(*searcher1, *searcher2);
				}
			}
			searcher1 = placeHolder;
		}
		searcher1 = bestDir;
		errorCounter++;
		if (errorCounter > 100) // if can't connect for too long it can go trough walls
		{
			ignoreIsWall = true;
			errorCounter = 0;
		}
		searcher1->unmake_obstacle();
	}
	searcher1->unmake_obstacle();
}


void BspMapGen::chceck_sizes(int levelmax, int MIN_SIZE)
{
	if (MYHEIGHT < (MIN_SIZE + 1) * pow(2, levelmax) &&
		MYLENGTH < (MIN_SIZE + 1) * pow(2, levelmax))
		throw "\nTOO_SMALL FIELD FOR THAT TREE LEVEL\n change CONFIGURATION.h";
}

