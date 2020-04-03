#pragma once

#include "../ECS/System.h"



class Attack final : public System
{
private:
	

public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;


};

