#include "pch.h"
#include "GAME_Printer.h"

#include "Level.h"
#include "Place.h"

GAME_Printer::GAME_Printer(const GAME& game) 
	: g(game)
{
	if (GAME_MODE_ASCII)
		load_textures_ASCII();
	else
		load_textures();



	LOG("GAME Printer.......................initialized");
}

GAME_Printer::~GAME_Printer()
{

	for (sf::Sprite x : textures)
		delete x.getTexture();
}



//void GAME_Printer::print_field()
//{
//	g.windowHandle->clear();
//	SharedPtr<sf::Sprite> tile;
//	int x, y;
//
//	for (int i = 0; i < MYHEIGHT; i++)
//	{
//		for (int j = 0; j < MYLENGTH; j++)
//		{
//			x = g.levelActive->get_fieldRef()[i][j]->get_x() * (TILE_SIZE + TILE_GAP);
//			y = g.levelActive->get_fieldRef()[i][j]->get_y() * (TILE_SIZE + TILE_GAP);
//
//			tile = g.levelActive->get_fieldRef()[i][j]->get_sprite_to_print();
//			////// stairs are alwas visible
//			if (g.levelActive->get_fieldRef()[i][j]->get_connector().stairsUp)
//				tile->setColor(MCOL::brown);
//			if (g.levelActive->get_fieldRef()[i][j]->get_connector().starisDown)
//				tile->setColor(sf::Color::Yellow);
//			///////
//			tile->setPosition((float)x, (float)y);
//			g.windowHandle->draw(*tile);
//		}
//	}
//	//UI::draw_player_UI(g.player);
//	g.windowHandle->display();
//}



void GAME_Printer::print_field_with_camera(Position pos)
{
	g.windowHandle->clear();
	SharedPtr<sf::Sprite> tile;
	int x, y;

	int camX = pos.x;
	int camY = pos.y;


	int lentghTilesHalf = LENGTH_TILES / 2;
	int heightTilesHalf = HEIGHT_TILES / 2;

	//camera bounds
	static int xLeft = 0, xRight = MYLENGTH, yUp = 0, yDown = MYHEIGHT;

	if (LENGTH_TILES < MYLENGTH || HEIGHT_TILES < MYHEIGHT)
	{
		if ((camX - lentghTilesHalf) <= 0)
		{
			xLeft = 0;
			xRight = LENGTH_TILES;
		}
		else if ((camX + lentghTilesHalf) > MYLENGTH)
		{
			xRight = MYLENGTH;
			xLeft = MYLENGTH - LENGTH_TILES;
		}
		else
		{
			xRight = camX + lentghTilesHalf;
			xLeft = camX - lentghTilesHalf;
		}

		if ((camY - heightTilesHalf) <= 0)
		{
			yUp = 0;
			yDown = HEIGHT_TILES;

		}
		else if ((camY + heightTilesHalf) >= MYHEIGHT)
		{
			yDown = MYHEIGHT;	
			yUp = MYHEIGHT - HEIGHT_TILES;
		}
		else
		{
			yUp = camY - heightTilesHalf;
			yDown = camY + heightTilesHalf + 1;
		}
	}

	for (int i = 0; i < (yDown - yUp); i++)
	{
		for (int j = 0; j < (xRight - xLeft); j++)
		{
			x = j * (TILE_LENGTH + TILE_GAP);
			y = i * (TILE_HEIGHT + TILE_GAP);

			tile = g.levelActive->get_fieldRef()[i + yUp][j + xLeft]->get_sprite_to_print();
			////// stairs are alwas visible
			if (g.levelActive->get_fieldRef()[i + yUp][j + xLeft]->get_connector().stairsUp)
				tile->setColor(MCOL::brown);
			if (g.levelActive->get_fieldRef()[i + yUp][j + xLeft]->get_connector().starisDown)
				tile->setColor(sf::Color::Red);
			///////
			tile->setPosition((float)x, (float)y);
			g.windowHandle->draw(*tile);
			}
	}
	//UI::draw_player_UI(g.player);
	g.windowHandle->display();
}


//void GAME_Printer::print_field_all_visible()
//{
//	g.windowHandle->clear();
//	SharedPtr<sf::Sprite> tile;
//	int x, y;
//
//	for (int i = 0; i < MYHEIGHT; i++)
//	{
//		for (int j = 0; j < MYLENGTH; j++)
//		{
//			x = g.levelActive->get_fieldRef()[i][j]->get_x() * TILE_SIZE;
//			y = g.levelActive->get_fieldRef()[i][j]->get_y() * TILE_SIZE;
//
//			tile = g.levelActive->get_fieldRef()[i][j]->get_sprite_to_print();
//			tile->setPosition((float)x, (float)y);
//			tile->setColor(sf::Color::White);
//			g.windowHandle->draw(*tile);
//		}
//	}
//	//UI::draw_player_UI(g.player);
//	g.windowHandle->display();
//}




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
	sf::Sprite sprite;
	std::string texturesPath = "../res/textures";
	sf::Texture* texture;

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/wallRock.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("wallRock.png.......................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/floor.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("floor.png..........................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/wallBrick.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("wallBrick.png......................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/player.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("player.png.........................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/sword.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("sword.png..........................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/rat.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("rat.png............................loaded");

	texture = new sf::Texture;	LOG_NEW;
	texture->loadFromFile(texturesPath + "/junkScarab.png");
	sprite.setTexture(*texture);
	textures.push_back(sprite);
	LOG("junkScarab.png.....................loaded");
}



void GAME_Printer::load_textures_ASCII()
{
	const int ROWS = 16;
	const int COLS = 16;
	const int SIZE = 16; // pixels

	sf::Sprite image;// (sf::Vector2f(20.0, 20.0));
	LOG_NEW;
	sf::Texture* texture = new sf::Texture;

	image.setTexture(*texture);

	std::string texturesPath = "../res/textures";
	texturesPath += "/sheet_16.png";
	if (texture->loadFromFile(texturesPath))
		LOG("ASCII textures loaded");

	sf::Vector2u textureSize = texture->getSize();
	textureSize.x /= COLS;
	textureSize.y /= ROWS;

	// wallRock
	image.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 11, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// floor
	image.setTextureRect(sf::IntRect(textureSize.x * 10, textureSize.y * 15, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// wallBrick
	image.setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 2, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// player
	image.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 3, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// sword
	image.setTextureRect(sf::IntRect(textureSize.x * 12, textureSize.y * 5, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// rat
	image.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 7, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

	// junkScarab
	image.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 7, textureSize.x, textureSize.y));
	textures.push_back(sf::Sprite(image));

}