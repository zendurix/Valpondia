#pragma once    
// component of GAME class, responsible for displaying graphics, and loading textures

#include "GAME.h"

class GAME;

class GAME_Printer
{
	friend class GAME;
private:
	const GAME& g;


	GAME_Printer(const GAME& game);
	~GAME_Printer();

	void load_textures();
	void load_textures_ASCII();

public:

	std::vector <sf::Sprite> textures;


	void print_field();
	void print_field_with_camera(Position pos);
	void print_field_all_visible();
};