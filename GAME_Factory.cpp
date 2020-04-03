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




Entity GAME_Factory::make_rat(SharedPtr<Place> place)
{
	Entity rat = g.ecs->create_entity();

	Position pos = Position{ place->get_x(), place->get_y(), place->get_levelID() };

	g.ecs->add_component(rat, Actor{});
	g.ecs->add_component(rat, pos);
	g.ecs->add_component(rat, Vision{ 10 });
	g.ecs->add_component(rat, AI{});
	g.ecs->add_component(rat, Name{ strCol{"rat", sf::Color::White} });
	g.ecs->add_component(rat, Render{ std::make_shared<sf::Sprite>(texturesPtr->at(static_cast<int>(TextureType::rat))) });


	Signature newSignature = g.ecs->get_signature(rat);
	g.ecs->signature_changed(rat, newSignature);
	place->go_here(rat);

	return rat;
}







Entity GAME_Factory::make_junkScarab(SharedPtr<Place> place)
{
	Entity junkScarab = g.ecs->create_entity();

	Position pos = Position{ place->get_x(), place->get_y(), place->get_levelID() };

	g.ecs->add_component(junkScarab, Actor{});
	g.ecs->add_component(junkScarab, pos);
	g.ecs->add_component(junkScarab, Vision{ 5 });
	g.ecs->add_component(junkScarab, AI{});
	g.ecs->add_component(junkScarab, Name{ strCol{"junk scarab", sf::Color::Red} });
	g.ecs->add_component(junkScarab, Render{ std::make_shared<sf::Sprite>(texturesPtr->at(static_cast<int>(TextureType::junkScarab))) });


	Signature newSignature = g.ecs->get_signature(junkScarab);
	g.ecs->signature_changed(junkScarab, newSignature);
	place->go_here(junkScarab);

	return junkScarab;
}