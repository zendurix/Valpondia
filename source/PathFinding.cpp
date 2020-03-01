#include "pch.h"
#include "PathFinding.h"

#include "Place.h"
#include "general_purpose_func.h"



PathFinding::AstarNode::AstarNode(SharedPtr<Place> place, SharedPtr<AstarNode> parent)
	: placePtr(place), parentNode(parent)
{
	placeX = place->get_x();
	placeY = place->get_y();
}




char PathFinding::calculate_dir(SharedPtr<Place> const origin, SharedPtr<Place> const target)
{
	int x1 = origin->get_x();
	int y1 = origin->get_y();
	int x2 = target->get_x();
	int y2 = target->get_y();

	if (x2 == x1 - 1)
	{
		if (y2 == y1)		return '4';
		if (y2 == y1 - 1)	return '7';
		if (y2 == y1 + 1)	return '1';
	}
	if (x2 == x1 + 1)
	{
		if (y2 == y1)		return '6';
		if (y2 == y1 - 1)	return '9';
		if (y2 == y1 + 1)	return '3';
	}
	if (x2 == x1)
	{
		if (y2 == y1 - 1)	return '8';
		if (y2 == y1 + 1)	return '2';
	}
	return '5';
}





char PathFinding::best_dir(const Vector2D<SharedPtr<Place>> *field, const SharedPtr<Place> start, const SharedPtr<Place> target)
{
	fieldRef = field;
	std::pair<int, char> result = Astar_path_dir_dist(start, target);

	return result.first;
}
// ADD check if path can't be found







std::pair<char, int> PathFinding::Astar_path_dir_dist(SharedPtr<Place> start, SharedPtr<Place> end)
{
	auto calc_h = [&](AstarNode curr)
	{
		return std::max(abs(curr.placeX - end->get_x()), abs(curr.placeY - end->get_y())) +
			+std::min(abs(curr.placeX - end->get_x()), abs(curr.placeY - end->get_y())) * DISTANCE_DIAG_ADD;
	};

	auto calc_g = [&](bool diag) {return (diag) ? q.g + DISTANCE_DIAG : q.g + DISTANCE; };

	std::vector <AstarNode> openVec;
	std::vector <AstarNode> closedVec;

	AstarNode starting(start, nullptr);
	starting.h = calc_h(starting);
	starting.g = 0;
	starting.f = starting.h + starting.g;
	openVec.push_back(starting);

	bool found = false;
	int qPos = 0;

	while (!found)
	{
		qPos = find_lowest_f_position(openVec);
		qPtr = std::make_shared<AstarNode>(openVec[qPos]);
		q = vector_pop(openVec, qPos);
		closedVec.push_back(q);

		if (q.placePtr == end) { found = true; break; }

		make_neighbours_of_q();

		for (AstarNode *node : q_neighbours)
		{
			if (node->placePtr != nullptr)
			{
				if (node->placePtr->get_isObstacle())
					continue;

				if (node->placePtr == end)
				{
					found = true;
					break;
				}

				node->h = calc_h(*node);

				char checkDir = calculate_dir(q.placePtr, node->placePtr);
				if (checkDir == '7' || checkDir == '9' || checkDir == '1' || checkDir == '3')
					node->g = calc_g(true);
				else
					node->g = calc_g(false);

				node->f = node->h + node->g;

				auto posList = std::find(openVec.begin(), openVec.end(), *node);
				auto posListChecked = std::find(closedVec.begin(), closedVec.end(), *node);

				if (posList != openVec.end())
				{ // if openVec contains same node, but with higher f it will be updated
					if (node->f < posList->f)
					{
						std::replace(posList, posList, *posList, *node);
					}
				}
				else if (posListChecked != closedVec.end())
				{
					continue;
				}
				else
				{
					openVec.push_back(*node);
				}
			}
		}
	}

	std::vector<SharedPtr<Place>> path = make_path(closedVec, end);
	int distance = path.size() - 1;
	char dir = calculate_dir(start, path.at(path.size() - 2));

	return std::pair<char, int>(dir, distance);
}




int PathFinding::find_lowest_f_position(std::vector<AstarNode> nodes)
{
	float minF = 1000000;
	int minPos = -1;
	int size = nodes.size();
	for (int i = 0; i < size; i++)
	{
		if (nodes[i].f < minF)
		{
			minF = nodes[i].f;
			minPos = i;
		}
	}
	return minPos;
}





void PathFinding::make_neighbours_of_q()
{
	if (q.placeX > 0)
	{
		q4 = AstarNode((*fieldRef)[q.placeY][q.placeX - 1], qPtr);

		if (q.placeY > 0)	q7 = AstarNode((*fieldRef)[q.placeY - 1][q.placeX - 1], qPtr);
		else                q7 = AstarNode(nullptr, qPtr);

		if (q.placeY < MYHEIGHT - 1)	q1 = AstarNode((*fieldRef)[q.placeY + 1][q.placeX - 1], qPtr);
		else					    q1 = AstarNode(nullptr, qPtr);
	}
	else
	{
		q4 = AstarNode(nullptr, qPtr);
		q7 = AstarNode(nullptr, qPtr);
		q1 = AstarNode(nullptr, qPtr);
	}

	if (q.placeX < MYLENGTH - 1)
	{
		q6 = AstarNode((*fieldRef)[q.placeY][q.placeX + 1], qPtr);

		if (q.placeY > 0)	q9 = AstarNode((*fieldRef)[q.placeY - 1][q.placeX + 1], qPtr);
		else                q9 = AstarNode(nullptr, qPtr);

		if (q.placeY < MYHEIGHT - 1)	q3 = AstarNode((*fieldRef)[q.placeY + 1][q.placeX + 1], qPtr);
		else					        q3 = AstarNode(nullptr, qPtr);
	}
	else
	{
		q6 = AstarNode(nullptr, qPtr);
		q9 = AstarNode(nullptr, qPtr);
		q3 = AstarNode(nullptr, qPtr);
	}

	if (q.placeY > 0) q8 = AstarNode((*fieldRef)[q.placeY - 1][q.placeX], qPtr);
	else			  q8 = AstarNode(nullptr, qPtr);

	if (q.placeY < MYHEIGHT - 1) q2 = AstarNode((*fieldRef)[q.placeY + 1][q.placeX], qPtr);
	else						 q2 = AstarNode(nullptr, qPtr);
}





bool PathFinding::vect_contains_same_node_lower_f(std::vector<AstarNode> &vec, AstarNode checkNode)
{
	for (AstarNode node : vec)
	{
		if (node.placeX == checkNode.placeX && node.placeY == checkNode.placeY)
		{
			if (node.f < checkNode.f)
				return true;
		}
	}
	return false;
}




std::vector<SharedPtr<Place>> PathFinding::make_path(std::vector<AstarNode> nodes, SharedPtr<Place> end)
{
	std::vector<AstarNode> nodesPath;
	std::vector<SharedPtr<Place>> path;

	path.push_back(end);
	path.push_back(nodes[nodes.size() - 1].placePtr);
	nodesPath.push_back(nodes[nodes.size() - 1]);

	while (nodesPath[nodesPath.size() - 1].parentNode != nullptr)
	{
		path.push_back(nodesPath[nodesPath.size() - 1].parentNode->placePtr);
		nodesPath.push_back(*nodesPath[nodesPath.size() - 1].parentNode);
	}
	return path;
}


