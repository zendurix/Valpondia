#pragma once

#include "../ECS/System.h"

class Place;

class Act final : public System
{
private:
	void act_player(Entity player);
	void act_AI(Entity ai);
public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;


	bool sees_this_place(Entity entity, SharedPtr<Place> place);
};
