#include "pch.h"
#include "GAME_Printer.h"

#include "Level.h"
#include "Place.h"

GAME_Printer::GAME_Printer(const GAME& game) 
	: g(game)
{
	load_textures();
	load_textures_ASCII();
}

GAME_Printer::~GAME_Printer()
{
	for (sf::Sprite x : textures)
		delete x.getTexture();
	for (sf::Sprite x : texturesASCII)
		delete x.getTexture();
}



void GAME_Printer::print_field()
{
	g.windowHandle->clear();
	SharedPtr<sf::Sprite> tile;
	int x, y;

	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			x = g.levelActive->get_fieldRef()[i][j]->get_x() * (TILE_SIZE + TILE_GAP);
			y = g.levelActive->get_fieldRef()[i][j]->get_y() * (TILE_SIZE + TILE_GAP);

			tile = g.levelActive->get_fieldRef()[i][j]->get_sprite_to_print();
			////// stairs are alwas visible
			if (g.levelActive->get_fieldRef()[i][j]->get_connector().stairsUp)
				tile->setColor(MCOL::brown);
			if (g.levelActive->get_fieldRef()[i][j]->get_connector().starisDown)
				tile->setColor(sf::Color::Yellow);
			///////
			tile->setPosition((float)x, (float)y);
			g.windowHandle->draw(*tile);
		}
	}
	//UI::draw_player_UI(g.player);
	g.windowHandle->display();
}


void GAME_Printer::print_field_all_visible()
{
	g.windowHandle->clear();
	SharedPtr<sf::Sprite> tile;
	int x, y;

	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			x = g.levelActive->get_fieldRef()[i][j]->get_x() * TILE_SIZE;
			y = g.levelActive->get_fieldRef()[i][j]->get_y() * TILE_SIZE;

			tile = g.levelActive->get_fieldRef()[i][j]->get_sprite_to_print();
			tile->setPosition((float)x, (float)y);
			tile->setColor(sf::Color::White);
			g.windowHandle->draw(*tile);
		}
	}
	//UI::draw_player_UI(g.player);
	g.windowHandle->display();
}




/*


void GAME_Printer::setupTexture(sf::Sprite &sprite, SharedPtr<Place> place, bool test)
{

	std::vector<sf::Sprite>* texturesUsed;
	if (!GAME_MODE_ASCII)
		texturesUsed = &textures;
	else
		texturesUsed = &texturesASCII;


	switch (place->get_printFormat())
	{
	case STD_WALL:
		sprite = (*texturesUsed)[rock_wall];
		break;
	case STD_FLOOR:
		sprite = (*texturesUsed)[floor_tile];
		break;
	case '@':
		sprite = (*texturesUsed)[player_tile];
		break;
	case '/':
		sprite = (*texturesUsed)[sword_tile];
		break;
	default:  //wals
		sprite = (*texturesUsed)[stone_wall];
		break;
	}












	if (place->get_printFormat() == '@')
	{
		if (!place->get_characterHere()->get_isAI())
			sprite.setColor(sf::Color::Green);
		else
			sprite.setColor(sf::Color::Red);
	}
	else if (place->get_characterHere() != nullptr && place->get_characterHere()->get_isAI())
		sprite.setColor(sf::Color::Red);
	else if (place->get_visible())
	{
		if (place->get_stairsDown())
		{
			sprite = textures[stone_wall];
			sprite.setColor(sf::Color::Yellow);
		}
		else if (place->get_stairsUp())
		{
			sprite = textures[stone_wall];
			sprite.setColor(sf::Color::Red);
		}
		else
			sprite.setColor(sf::Color::White);
	}
	else if (place->get_wasSeen())
		sprite.setColor(MCOL::grey);
	else if (test)
		sprite.setColor(sf::Color::White);
	else
		sprite.setColor(sf::Color::Black);


	//////////////////////////////////// stairs are always visible
	if (place->get_stairsDown())
	{
		sprite = textures[stone_wall];
		sprite.setColor(sf::Color::Yellow);
	}
	if (place->get_stairsUp())
	{
		sprite = textures[stone_wall];
		sprite.setColor(MCOL::brown);
	}
	////////////////////////////////////////
}




*/

































void GAME_Printer::load_textures()
{
	sf::Sprite rock_wall;
	sf::Sprite floor_tile;
	sf::Sprite stone_wall;
	sf::Sprite player_tile;
	sf::Sprite sword_tile;

	std::string texturesPath = "../res/textures";

	sf::Texture* texture1 = new sf::Texture;
	LOG_NEW;
	texture1->loadFromFile(texturesPath + "/wallRock.png");
	rock_wall.setTexture(*texture1);
	textures.push_back(rock_wall);
	LOG("wallRock.png.......................loaded");

	sf::Texture* texture3 = new sf::Texture;
	LOG_NEW;
	texture3->loadFromFile(texturesPath + "/floor.png");
	floor_tile.setTexture(*texture3);
	textures.push_back(floor_tile);
	LOG("floor.png..........................loaded");

	sf::Texture* texture2 = new sf::Texture;
	LOG_NEW;
	texture2->loadFromFile(texturesPath + "/wallBrick.png");
	stone_wall.setTexture(*texture2);
	textures.push_back(stone_wall);
	LOG("wallBrick.png......................loaded");

	sf::Texture* texture4 = new sf::Texture;
	LOG_NEW;
	texture4->loadFromFile(texturesPath + "/player.png");
	player_tile.setTexture(*texture4);
	textures.push_back(player_tile);
	LOG("player.png.........................loaded");

	sf::Texture* texture5 = new sf::Texture;
	LOG_NEW;
	texture5->loadFromFile(texturesPath + "/sword.png");
	sword_tile.setTexture(*texture5);
	textures.push_back(sword_tile);
	LOG("sword.png..........................loaded");
}



void GAME_Printer::load_textures_ASCII()
{
	const int ROWS = 16;
	const int COLS = 16;
	const int SIZE = 20; // pixels

	sf::Sprite image;// (sf::Vector2f(20.0, 20.0));
	LOG_NEW;
	sf::Texture* texture = new sf::Texture;

	image.setTexture(*texture);

	std::string texturesPath = "../res/textures";
	texturesPath += "/Anikki_square_20x20.bmp";
	if (texture->loadFromFile(texturesPath))
		LOG("ASCII textures loaded");

	sf::Vector2u textureSize = texture->getSize();
	textureSize.x /= COLS;
	textureSize.y /= ROWS;

	// wallRock
	image.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 11, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));

	// floor
	image.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));

	// wallBrick
	image.setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 2, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));

	// player
	image.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 3, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));

	// sword
	image.setTextureRect(sf::IntRect(textureSize.x * 12, textureSize.y * 5, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));

	// rat
	image.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 7, textureSize.x, textureSize.y));
	texturesASCII.push_back(sf::Sprite(image));


}