#include "pch.h"
#include "BspMapGen.h"

std::vector<SharedPtr<Room>> BspMapGen::make_dung_map_ret_rooms(Vector2D<SharedPtr<Place>> &field, bool test)
{
	GAME* game = GAME::getInstance();
	std::vector <SharedPtr <Room>> rooms;

	BspMapGen tree(test);

	int restart_count = 0;
	bool restart = false;
	while (!restart)
	{
		try
		{
			tree.make_full_tree();
			restart = true;
		}
		catch (...)
		{
			restart = false;
			restart_count++;
			for (int i = 0; i < MYHEIGHT; i++)
				for (int j = 0; j < MYLENGTH; j++)
					game->levelActive->field[i][j]->RESET();
		}
	}

	LOG("BSP tree restart count: " << restart_count);

	tree.fill_leaves_with_rooms(&rooms);
	tree.connect_all_rooms();

	if (test)
	{
		for (int i = 0; i < MYHEIGHT; i++)
			for (int j = 0; j < MYLENGTH; j++)
				game->levelActive->field[i][j]->set_tileColor(sf::Color::White);
	}
	tree.~tree();
	return rooms;
}



BspMapGen::BspMapGen(bool test)
{
	// to actually make a full tree call make_full_tree method
	// this was split into other method, due to restarting problem
	testing = test;
}

BspMapGen::~BspMapGen()
{
	root_node = nullptr;
	nodes.clear();
	Node::nodeCount = -1;
	Node::level = 0;
}


void BspMapGen::make_full_tree()
{
	game = GAME::getInstance();
	std::vector <std::vector <SharedPtr<Place> > > &field = game->levelActive->field;
	int actual_level;
	nodesNum = 0;
	for (int i = 0; i <= MAX_LEVEL; i++)
	{
		nodesNum += (int)pow(2, i);
	}

	root_node = std::make_unique<Node>(MAX_LEVEL, field[0][0], MYLENGTH, MYHEIGHT, 0);
	nodes.push_back(std::move(root_node));

	for (int i = 0; i < MAX_LEVEL; i++)
	{
		actual_level = root_node->level;

		for (int j = (int)pow(2, actual_level) - 1; j <= (int)pow(2, actual_level + 1) - 2; j++)
		{
			if (!split_dungeon_BSP(nodes[j]->fieldNode, nodes[j], actual_level))
			{ // RNG failed (loops over 200 times)
				Node::level = 0;
				Node::nodeCount = -1;
				root_node = nullptr;
				nodes.clear();
				throw "false";
			}
		}
	}

	if(testing) // print split steps, and room connection steps
	{
		for (int k = 0; k <= MAX_LEVEL; k++)
		{
			for (int i = 0; i < MYHEIGHT; i++)
				for (int j = 0; j < MYLENGTH; j++)
					field[i][j]->set_tileColor(sf::Color::White);

			for (std::unique_ptr<Node> &node : nodes)
			{
				if (node->levelIndex == k)
				{
					for (int i = node->fieldNode->get_x(); i < node->fieldNode->get_x() + node->length; i++)
					{
						field[node->fieldNode->get_y()][i]->set_tileColor(sf::Color::Red);
						field[node->fieldNode->get_y() + node->height - 1][i]->set_tileColor(sf::Color::Red);
					}
					for (int i = node->fieldNode->get_y(); i < node->fieldNode->get_y() + node->height; i++)
					{
						field[i][node->fieldNode->get_x()]->set_tileColor(sf::Color::Red);
						field[i][node->fieldNode->get_x() + node->length - 1]->set_tileColor(sf::Color::Red);
					}
				}
			}
			game->Printer->print_field_BSP_show(false, nodes);
			wait_for_input(space);
		}
	}
}


bool BspMapGen::split_dungeon_BSP(SharedPtr<Place> field, std::unique_ptr<Node> &parent, int level)
{ // field is parent->field-node   // returns false, when error
	std::unique_ptr<Node> node1, node2;
	bool orientation = random(0, 1);
	int length1, length2, height1, height2;
	int x, y;
	int error = 0;

	if (orientation == 0) // horizontal
	{
		do
		{
			y = random(parent->fieldNode->get_y() + parent->height / 2 - MIN_SIZE / 2,
				parent->fieldNode->get_y() + parent->height / 2 + MIN_SIZE / 2);
			length1 = parent->length;
			length2 = length1;
			height1 = y - parent->fieldNode->get_y();
			height2 = parent->height - height1;
			error++;
			if (error > 200)
			{
				return false;
			}

		} while (height1 < MIN_SIZE + 1 || height2 < MIN_SIZE + 1);
	}
	else if (orientation == 1)  // vertical
	{
		do
		{
			x = random(parent->fieldNode->get_x() + parent->length / 2 - MIN_SIZE / 2,
				parent->fieldNode->get_x() + parent->length / 2 - MIN_SIZE / 2);
			length1 = x - parent->fieldNode->get_x();
			length2 = parent->length - length1;
			height1 = parent->height;
			height2 = parent->height;
			error++;
			if (error > 200)
			{
				return false;
			}

		} while (length1 < MIN_SIZE + 1 || length2 < MIN_SIZE + 1);
	}

	node1 = std::make_unique<Node>(MAX_LEVEL, field, length1, height1, orientation);

	int fieldX = field->get_x();
	int fieldY = field->get_y();

	if (orientation == 0)
	{
		fieldY += height1;
	}
	else
	{
		fieldX += length1;
	}

	field = game->levelActive->field[fieldY][fieldX];

	node2 = std::make_unique<Node>(MAX_LEVEL, field, length2, height2, orientation);

	make_children(node1, node2, parent);
	nodes.push_back(std::move(node1));
	nodes.push_back(std::move(node2));
	return true;
}

void BspMapGen::fill_leaves_with_rooms(std::vector <SharedPtr <Room>> *rooms)
{
	make_whole_map_obstacle();
	int length1, height1;
	int x1, y1;
	SharedPtr <Room> room;
	for (int i = 0; i < nodesNum; i++)
	{
		if (nodes[i]->isLeaf)
		{
			do
			{
				length1 = random(MIN_SIZE - 2, nodes[i]->length - 3);
				height1 = random(MIN_SIZE - 2, nodes[i]->height - 3);
			} while ((double)height1 / length1 < ROOM_WALLS_PROPORTION ||
					 (double)length1 / height1 < ROOM_WALLS_PROPORTION  );

			if (nodes[i]->fieldNode->get_x() + 2 < (nodes[i]->fieldNode->get_x() + nodes[i]->length) - (length1 + 2))
				x1 = random(nodes[i]->fieldNode->get_x() + 1, (nodes[i]->fieldNode->get_x() + nodes[i]->length) - (length1 + 2));
			else
				x1 = nodes[i]->fieldNode->get_x() + 1;


			if (nodes[i]->fieldNode->get_y() + 2 < (nodes[i]->fieldNode->get_y() + nodes[i]->height) - (height1 + 2))
				y1 = random(nodes[i]->fieldNode->get_y() + 1, (nodes[i]->fieldNode->get_y() + nodes[i]->height) - (height1 + 2));
			else
				y1 = nodes[i]->fieldNode->get_y() + 1;


			if (y1 + height1 + 1 >= MYHEIGHT- 1)
				height1--;
			if (x1 + length1 + 1 >= MYLENGTH - 1)
				length1--;

			
			room = std::make_shared<Room>();

			make_room("rectangle", x1, y1, length1, height1, room, "", false);

			nodes[i]->room = room;
			rooms->push_back(room);
		}
	}
	for (int i = 0; i < nodesNum; i++)
	{
		if (nodes[i]->isLeaf)
		{
			nodes[i]->check_family();
		}
	}
	if (testing)
	{
		game->Printer->print_field_BSP_show(true, nodes);
		wait_for_input(space);
	}

}

void BspMapGen::connect_all_rooms()
{
	std::vector <std::vector <SharedPtr<Place> > > &field = game->levelActive->field;
	SharedPtr<Place> searcher1 = nullptr, searcher2 = nullptr;
	Node* node1 = nullptr, *node2 = nullptr;
	bool horizontalConnection;
	bool found = false;
	bool child;	
	int add_connections = 3, counter = 0; // to add more connections on first level of the tree

	for (int j = MAX_LEVEL; j > 0; j--)
	{
		for (int i = (int)pow(2, j) - 1; i < (int)pow(2, j + 1) - 2;
			i += (j != 1) ? 2 : ((counter < add_connections) ? 0 : 2))
		{
			counter += (j == 1) ? 1 : 0;
			found = false;
			while (!found)
			{
				node1 = nodes[i].get();
				node2 = nodes[i + 1].get();
				while (node1->childreen[0] != nullptr)
				{
					child = random(0, 1);
					node1 = node1->childreen[child];
					node2 = node2->childreen[child];
				}

				if (nodes[i]->horizontal)
				{
					if (node2->room->cornerNW.x >= node1->room->cornerNE.x)
						found = true;
				}
				else  // vertical
				{
					if (node2->room->cornerNE.y >= node1->room->cornerSE.y)
						found = true;
				}
			}

			horizontalConnection = (node2->room->cornerNE.y - node1->room->cornerSE.y >=
				node2->room->cornerNW.x - node1->room->cornerNE.x) ? 0 : 1;


			if (horizontalConnection) //(nodes[i]->horizontal)
			{
				searcher1 = field[node1->room->cornerNE.cornerPtr->get_y() + 2][node1->room->cornerNE.cornerPtr->get_x()];
				searcher2 = field[node2->room->cornerNW.cornerPtr->get_y() + 2] [node2->room->cornerNW.cornerPtr->get_x()];
			}													  
			else // vertical									  
			{													  
				searcher1 = field[node1->room->cornerSW.cornerPtr->get_y()][node1->room->cornerSW.cornerPtr->get_x() + 2];
				searcher2 = field[node2->room->cornerNW.cornerPtr->get_y()][node2->room->cornerNW.cornerPtr->get_x() + 2];
			}

			connect_2_rooms(searcher1, searcher2); // node1->horizontal);
		}
		if (testing)
		{
			game->Printer->print_field_BSP_show(true, nodes);
			wait_for_input(space);
		}
	}
}

void BspMapGen::connect_2_rooms(SharedPtr<Place> searcher1, SharedPtr<Place>  searcher2)
{
	std::vector <std::vector <SharedPtr<Place> > > &field = game->levelActive->field;

	searcher1->unmake_obstacle();
	static SharedPtr<Place>  bestDir = searcher1;
	static SharedPtr<Place>  searcher1START = searcher1;
	static SharedPtr<Place>  placeHolder = nullptr;
	int error_counter = 0;
	double bestDist;
	bool bestFound = false;
	bool ignoreIsWall = false;

	//if searcher is on edge of map place it on different corner of room
	if (searcher1->get_x() == 0 || searcher1->get_y() == 0)
		searcher1 = field[searcher1->get_roomHere()->cornerSE.y][searcher1->get_roomHere()->cornerSE.x - 1];
	if (searcher1->get_x() == MYLENGTH - 1 || searcher1->get_y() == MYHEIGHT - 1)
		searcher1 = field[searcher1->get_roomHere()->cornerNW.y][searcher1->get_roomHere()->cornerNW.x + 1];

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
				case 1:	if CHECKbth searcher1 = field[searcher1->get_y() + 1][searcher1->get_x() - 1];	break;
				case 2:	if CHECKmax searcher1 = field[searcher1->get_y() + 1][searcher1->get_x()];		break;
				case 3:	if CHECKmax searcher1 = field[searcher1->get_y() + 1][searcher1->get_x() + 1];	break;
				case 4:	if CHECKmin searcher1 = field[searcher1->get_y()]    [searcher1->get_x() - 1];	break;
				case 5:	continue;																	break;
				case 6:	if CHECKmax searcher1 = field[searcher1->get_y()]    [searcher1->get_x() + 1];	break;
				case 7:	if CHECKmin searcher1 = field[searcher1->get_y() - 1][searcher1->get_x() - 1];	break;
				case 8:	if CHECKmin searcher1 = field[searcher1->get_y() - 1][searcher1->get_x()];		break;
				case 9:	if CHECKbth searcher1 = field[searcher1->get_y() - 1][searcher1->get_x() + 1];	break;
			}

			if (ignoreIsWall || !searcher1->get_isWall() || searcher1 == searcher2)   
			{
				if (searcher1 == searcher2)
				{
					int aaa = 3;
				}
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
		error_counter++;
		if (error_counter > 100)
		{
			ignoreIsWall = true;
			error_counter = 0;
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

