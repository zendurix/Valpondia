#pragma once

#include "pch.h"


const bool DEBUG_MENU = true; // show simplified menu

const bool GAME_MODE_ASCII = true;


enum lvType { cave = 0, dungeon = 1, fromFile = 2, ruins };


typedef std::pair<lvType, std::string> lvPair;
const std::vector< lvPair > LEVEL_ORDER = { lvPair(ruins, ""), lvPair(fromFile, "valpondia_palace.txt"), 
											lvPair(dungeon, ""), lvPair(dungeon, ""), lvPair(cave, ""), lvPair(cave, "") };






// useful shortcuts for often used types
template <typename T>
using Vector2D = std::vector <std::vector<T>>;
template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T>
using UniquePtr = std::unique_ptr<T>;


// WINDOW SIZES
const int MYHEIGHT = 50;  // y axis
const int MYLENGTH = 70;  // x axis
const int UI_LENGTH = 200;  // length from right border
const int TILE_SIZE = 20; // in pixels
const int WIN_HEIGHT = MYHEIGHT * TILE_SIZE;
const int WIN_LENGTH = MYLENGTH * TILE_SIZE + UI_LENGTH;
const int CHAR_SIZE = 32;  // size of text
//


// RUINS MAP
const int RUINS_MIN = 12;
const int RUIN_MAX = 16;


//



// MAKING TREE (generating random map):
const int MAX_LEVEL = 4;
const int MIN_ROOM_SIZE = 5;
const double ROOM_WALLS_PROPORTION = 3.0 / 8.0;
const int PLACE_FOR_WALLS = 2;
//



// standard chars
const char STD_FLOOR = '.';
const char STD_WALL = '#';
const char STD_ESC = '\b';
//



// ITEMS enum and consts
enum class itemType		{ weapon = 0, armor, potion };
enum class ItemOpt		{ none = -1, look = 0, drop, equip, unequip, use };
enum class itemMaterial { cardboard = 0, nonSpecific, cloth, leather, iron, rubber, steel };
enum class BodyPart		{ none = -1, head = 0, body = 1, hands = 2, legs = 3, rHand = 4, lHand = 5, forHands };
enum class useType		{ noUse, drink, eat, throww };	
const int BODY_PARTS_COUNT = 6;
//

enum class Dir {up = '8', down = '2'};

// for FoV and Gen Func
static const float PI = 3.1415927f;
static const float ACCURACY = 0.00625f;
static const float DEGREE_STEP = 0.25f;
//



static int NEW_ALLOCATIONS = 0;

#define TESTING 1
#define PRINT_ALLOCATIONS 0
#if TESTING == 1             //_DEBUG == 1
	#define LOG(x) std::cout << x << std::endl;
	// macro to track any new allocations  (LOG_NEW; must be used after every allocations with "new" keyword)
	// not very useful anymore, since most raw ptrs are changed to smart ptrs
	#if PRINT_ALLOCATIONS  
		#define LOG_NEW {	\
							std::cout<<__FILE__<<" "<<__LINE__<<" alloc numb: "<<NEW_ALLOCATIONS<<std::endl; \
							NEW_ALLOCATIONS++; \
						}
	#else 
		#define LOG_NEW
	#endif 
	#else // replace macros with nothing (they won't be working)
		#define LOG(x)
		#define LOG_NEW
#endif
