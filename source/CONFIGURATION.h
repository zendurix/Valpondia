#pragma once

#include "pch.h"

#define TESTING 1
#define PRINT_ALLOCATIONS 1
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

static int NEW_ALLOCATIONS = 0;


const int MYHEIGHT = 50;  // y axis
const int MYLENGTH = 60;  // x axis

const int UI_LENGTH = 200;  // length from right border

const int TILE_SIZE = 16; // in pixels
const int WIN_HEIGHT = MYHEIGHT * TILE_SIZE;
const int WIN_LENGTH = MYLENGTH * TILE_SIZE + UI_LENGTH;

const int CHAR_SIZE = 32;  // size of text

// MAKING TREE (generating random map):
const int MAX_LEVEL = 4;
const int MIN_SIZE = 5;
const double ROOM_WALLS_PROPORTION = 3.0 / 8.0;


const char STD_FLOOR = '.';
const char STD_WALL = '#';



const char STD_ESC = '\b';


enum class itemType		{ weapon = 0, armor, potion };
enum class itemMaterial { cardboard = 0, nonSpecific, cloth, leather, iron, rubber, steel };
enum class BodyPart		{ head = 0, body = 1, hands = 2, legs = 3, rHand = 4, lHand = 5, forHands, none };
enum class useType		{ noUse, drink, eat, throww };
enum class Hand			{ none, lHand = 4, rHand = 5, twoHand }; // value for l/r Hand is equal to l/r Hand val in CodyPart
		
const int BODY_PARTS_COUNT = 6;
