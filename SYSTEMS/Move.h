#pragma once

#include "../ECS/System.h"


class Move final : public System  
{
private:
	bool border_cross(const Position& pos);
public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;
};

