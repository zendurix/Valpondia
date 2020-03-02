#include "pch.h"
#include "GAME_Factory.h"

#include "Level.h"
#include "Place.h"


GAME_Factory::GAME_Factory(GAME& game, std::vector <sf::Sprite>* texturesPointer) :
	g(game)
{
	texturesPtr = texturesPointer;

	LOG("GAME Factory.......................initialized");
}


GAME_Factory::~GAME_Factory()
{
}




Entity GAME_Factory::make_rat(Position pos)
{
	Entity rat = g.ecs->create_entity();

	g.ecs->add_component(rat, Actor{});
	g.ecs->add_component(rat, pos);
	g.ecs->add_component(rat, Vision{ 10 });
	g.ecs->add_component(rat, AI{});
	g.ecs->add_component(rat, Name{ strCol{"rat", sf::Color::White} });
	g.ecs->add_component(rat, Render{ std::make_shared<sf::Sprite>(texturesPtr->at(static_cast<int>(TextureType::rat))) });


	Signature newSignature = g.ecs->get_signature(rat);
	g.ecs->signature_changed(rat, newSignature);
	g.get_levels()->at(pos.levelID)->get_fieldRef()[pos.y][pos.x]->go_here(rat);


}







