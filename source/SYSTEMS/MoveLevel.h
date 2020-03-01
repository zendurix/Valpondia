#pragma once

#include "../ECS/System.h"


class MoveLevel : public System
{
public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;
};

