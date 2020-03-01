#pragma once

#include "../ECS/System.h"


class Act final : public System
{
private:
	void act_player(Entity player);
	void act_AI(Entity ai);
public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;
};
