#pragma once    
// component of GAME class, responsible for displaying graphics, and loading textures


#include "GAME.h"
#include "colors.h"

class GAME;
class Node;

class GAME_Printer  
{
friend GAME;
private:
	GAME* g;
	std::vector <sf::Sprite> textures;
	enum textureNames { rock_wall = 0, floor_tile, stone_wall, player_tile, sword_tile };

	void load_textures();

	GAME_Printer(GAME* game);
	~GAME_Printer();

public:
	void print_field();
	void print_field_BSP_show(bool placedRooms, std::vector<std::unique_ptr<Node>> &nodes);
	void print_field_UPDATE();
	void setupTexture(sf::Sprite &sprite, SharedPtr<Place> place, bool test);
};