#pragma once


#include "general_purpose_func.h"
#include "Character.h"
#include "Place.h"



class PathFinding
{
private:
	PathFinding() = delete;
	~PathFinding() = delete;
	
	inline static std::vector <std::vector <SharedPtr<Place>>> *fieldRef;
	inline static const float DISTANCE = 1.f;
	inline static const float DISTANCE_DIAG_ADD = 0.8f; // this is big, so A/I will prefer walking straight than diagonally,
												// but lower than 1, so AI will still prefer walking 1 diag, than 2 straight
	inline static const float DISTANCE_DIAG = DISTANCE + DISTANCE_DIAG_ADD;

	struct AstarNode
	{
		SharedPtr<Place> placePtr;
		int placeY, placeX;
		union { float costFromStart; float g; };
		union { float costToEnd;     float h; };
		union { float costsSum;      float f; };
		SharedPtr<AstarNode> parentNode;

		AstarNode() {};
		AstarNode(SharedPtr<Place> place, SharedPtr<AstarNode> parent = nullptr, float costEnd = -1, float costStart = -1)
			: placePtr(place), costToEnd(costEnd), costFromStart(costStart), parentNode(parent)
		{
			costsSum = costStart + costEnd;
			placeX = place->get_x();
			placeY = place->get_y();
		}
		~AstarNode() {}
		bool operator == (const AstarNode& node)
		{
			//h == node.h && g == node.h &&
			if (placePtr == node.placePtr) return true;
			else return false;
		}
	};

	static inline const std::vector<AstarNode*> a;   // WTF without this line q_neighbours is martked as "incomplete type is not allowed"
	
	inline static AstarNode q;
	inline static SharedPtr< AstarNode> qPtr;
	inline static AstarNode q1, q2, q3, q4, q6, q7, q8, q9; // neighbours of q (numbers are directions from q, like on numpad)
	static inline const std::vector<AstarNode*> q_neighbours { &q1, &q2, &q3, &q4,  &q6, &q7, &q8, &q9 };




	static std::pair<char, int> Astar_path_dir_dist(SharedPtr<Place> start, SharedPtr<Place> end);
	static int find_lowest_f_pos(std::vector<AstarNode> nodes);
	static void make_q_neighbours();
	static bool vect_contains_same_node_lower_f(std::vector<AstarNode> &vec, AstarNode checkNode);
	static std::vector<SharedPtr<Place>> make_path(std::vector<AstarNode> nodes, SharedPtr<Place> end);
	static char calc_dir(SharedPtr<Place> origin, SharedPtr<Place> target);

public:

	static char best_dir(Character character, SharedPtr<Place>);

	static void set_fieldRef(std::vector <std::vector <SharedPtr<Place>>> *field) { fieldRef = field; }
	
};



