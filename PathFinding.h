#pragma once

#include "CONFIGURATION.h"


class Place;

class PathFinding
{
public:

	// returns '5' if no path was found
	static char best_dir(const Vector2D<SharedPtr<Place>> *field, const SharedPtr<Place> start, const SharedPtr<Place> target);

private:
	struct AstarNode
	{
		SharedPtr<Place> placePtr;
		int placeY, placeX;
		float g;
		float h;
		float f;
		SharedPtr<AstarNode> parentNode;

		AstarNode() {};
		AstarNode(SharedPtr<Place> place, SharedPtr<AstarNode> parent = nullptr);
		inline bool operator == (const AstarNode& node)
		{//h == node.h && g == node.h &&
			if (placePtr == node.placePtr) return true;
			else return false;
		}
	}; // struct AstarNode

	PathFinding() = delete;
	~PathFinding() = delete;

	// DISTANCE_DIAG_ADD is big, so AI will prefer walking straight than diagonally, ..
	// .. but lower than 1, so AI will still prefer walking 1 diag, than 2 straight	
	inline static const float DISTANCE_DIAG_ADD = 0.8f;
	inline static const float DISTANCE = 1.0f;
	inline static const float DISTANCE_DIAG = DISTANCE + DISTANCE_DIAG_ADD;


	inline static AstarNode q;
	inline static SharedPtr<AstarNode> qPtr;
	inline static AstarNode q1, q2, q3, q4, q6, q7, q8, q9; // neighbours of q (numbers are directions from q, like on numpad)
	inline static const std::vector<AstarNode*> q_neighbours{ &q1, &q2, &q3, &q4,  &q6, &q7, &q8, &q9 };

	inline static const std::vector <std::vector <SharedPtr<Place>>> *fieldRef;


	static std::pair<char, int> Astar_path_dir_dist(SharedPtr<Place> start, SharedPtr<Place> end);
	static int find_lowest_f_position(std::vector<AstarNode> nodes);
	static void make_neighbours_of_q();
	static bool vect_contains_same_node_lower_f(std::vector<AstarNode> &vec, AstarNode checkNode);
	static std::vector<SharedPtr<Place>> make_path(std::vector<AstarNode> nodes, SharedPtr<Place> end);
	static char calculate_dir(SharedPtr<Place> origin, SharedPtr<Place> target);
};



