#include "pch.h"
#include "GAME_Printer.h"

GAME_Printer::GAME_Printer(GAME* game)
{
	g = game;
	load_textures();
}

GAME_Printer::~GAME_Printer()
{
	for (sf::Sprite x : textures)
	{
		delete x.getTexture();
	}
}

void GAME_Printer::print_field()
{
	g->windowHandle->clear();
	sf::Sprite tile;
	int x, y;

	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			x = g->levelActive->field[i][j]->get_x() * TILE_SIZE;
			y = g->levelActive->field[i][j]->get_y() * TILE_SIZE;
			setupTexture(tile, g->levelActive->field[i][j], true);
			tile.setPosition((float)x, (float)y);
			g->windowHandle->draw(tile);
		}
	}
	g->windowHandle->display();
}


void GAME_Printer::print_field_BSP_show(bool placedRooms, std::vector<std::unique_ptr<Node>> &nodes)
{
	g->windowHandle->clear();
	sf::Sprite tile;
	int x, y;

	if (!placedRooms)
		make_whole_map_obstacle();

	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			x = g->levelActive->field[i][j]->get_x() * TILE_SIZE;
			y = g->levelActive->field[i][j]->get_y() * TILE_SIZE;
			setupTexture(tile, g->levelActive->field[i][j], true);
			if (g->levelActive->field[i][j]->get_tileColor() != MCOL::placeHolder)
				tile.setColor(g->levelActive->field[i][j]->get_tileColor());
			tile.setPosition((float)x, (float)y);
			g->windowHandle->draw(tile);
		}
	}
	sf::Text *text = init_text();
	for (std::unique_ptr<Node> &node : nodes)
	{
		if (node->isLeaf)
		{
			text->setString(node->make_family_list());

			text->setPosition((float)node->fieldNode->get_x() * TILE_SIZE, 
							  (float)node->fieldNode->get_y() * TILE_SIZE);
			text->setCharacterSize(20);
			text->setFillColor(sf::Color::White);
			text->setOutlineColor(sf::Color::Blue);
			text->setOutlineThickness(1);
			g->windowHandle->draw(*text);
		}
	}
	delete text;

	g->windowHandle->display();
}


void GAME_Printer::print_field_UPDATE()
{
	g->windowHandle->clear();
	sf::Sprite tile;
	int x, y;

	for (int i = 0; i < MYHEIGHT; i++)
	{
		for (int j = 0; j < MYLENGTH; j++)
		{
			x = g->levelActive->field[i][j]->get_x() * TILE_SIZE;
			y = g->levelActive->field[i][j]->get_y() * TILE_SIZE;

			setupTexture(tile, g->levelActive->field[i][j], false);
			tile.setPosition((float)x, (float)y);
			g->windowHandle->draw(tile);

		}
	}
	g->windowHandle->display();
}

void GAME_Printer::setupTexture(sf::Sprite &sprite, SharedPtr<Place> place, bool test)
{
	switch (place->get_printFormat())
	{
	case STD_WALL:
		sprite = textures[rock_wall];
		break;
	case STD_FLOOR:
		sprite = textures[floor_tile];
		break;
	case '@':
		sprite = textures[player_tile];
		break;
	case '/':
		sprite = textures[sword_tile];
		break;
	default:  //wals
		sprite = textures[stone_wall];
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

void GAME_Printer::load_textures()
{
	sf::Sprite rock_wall;
	sf::Sprite floor_tile;
	sf::Sprite stone_wall;
	sf::Sprite player_tile;
	sf::Sprite sword_tile;

	sf::Texture* texture1 = new sf::Texture;
	LOG_NEW;
	texture1->loadFromFile("../SFML/sources/16x16/wallRock.png");
	rock_wall.setTexture(*texture1);
	textures.push_back(rock_wall);

	sf::Texture* texture3 = new sf::Texture;
	LOG_NEW;
	texture3->loadFromFile("../SFML/sources/16x16/floor.png");
	floor_tile.setTexture(*texture3);
	textures.push_back(floor_tile);

	sf::Texture* texture2 = new sf::Texture;
	LOG_NEW;
	texture2->loadFromFile("../SFML/sources/16x16/wallBrick.png");
	stone_wall.setTexture(*texture2);
	textures.push_back(stone_wall);

	sf::Texture* texture4 = new sf::Texture;
	LOG_NEW;
	texture4->loadFromFile("../SFML/sources/16x16/player.png");
	player_tile.setTexture(*texture4);
	textures.push_back(player_tile);

	sf::Texture* texture5 = new sf::Texture;
	LOG_NEW;
	texture5->loadFromFile("../SFML/sources/16x16/sword.png");
	sword_tile.setTexture(*texture5);
	textures.push_back(sword_tile);
}