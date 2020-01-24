#pragma once


#include "general_purpose_func.h"
#include "Character.h"
#include "Place.h"



class PathFinding
{
private:
	PathFinding() = delete;
	~PathFinding() = delete;
	
	inline static std::vector <std::vector <std::shared_ptr<Place>>> *fieldRef;
	inline static const float DISTANCE = 1.f;
	inline static const float DISTANCE_DIAG_ADD = 0.8f; // this is big, so A/I will prefer walking straight than diagonally,
												// but lower than 1, so AI will still prefer walking 1 diag, than 2 straight
	inline static const float DISTANCE_DIAG = DISTANCE + DISTANCE_DIAG_ADD;

	struct AstarNode
	{
		std::shared_ptr<Place> placePtr;
		int placeY, placeX;
		union { float costFromStart; float g; };
		union { float costToEnd;     float h; };
		union { float costsSum;      float f; };
		std::shared_ptr<AstarNode> parentNode;

		AstarNode() {};
		AstarNode(std::shared_ptr<Place> place, std::shared_ptr<AstarNode> parent = nullptr, float costEnd = -1, float costStart = -1)
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
	inline static std::shared_ptr< AstarNode> qPtr;
	inline static AstarNode q1, q2, q3, q4, q6, q7, q8, q9; // neighbours of q (numbers are directions from q, like on numpad)
	static inline const std::vector<AstarNode*> q_neighbours { &q1, &q2, &q3, &q4,  &q6, &q7, &q8, &q9 };




	static std::pair<char, int> Astar_path_dir_dist(std::shared_ptr<Place> start, std::shared_ptr<Place> end);
	static int find_lowest_f_pos(std::vector<AstarNode> nodes);
	static void make_q_neighbours();
	static bool vect_contains_same_node_lower_f(std::vector<AstarNode> &vec, AstarNode checkNode);
	static std::vector<std::shared_ptr<Place>> make_path(std::vector<AstarNode> nodes, std::shared_ptr<Place> end);
	static char calc_dir(std::shared_ptr<Place> origin, std::shared_ptr<Place> target);

public:

	static char best_dir(Character character, std::shared_ptr<Place>);

	static void set_fieldRef(std::vector <std::vector <std::shared_ptr<Place>>> *field) { fieldRef = field; }
	
};



