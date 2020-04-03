#pragma once

#include "../CONFIGURATION.h"
#include "../ECS/System.h"


class EqManager final : public System
{
private:

	Entity currentEntity;	
	Equipment& equipment;
	Inventory& inventory;



	void equip(BodyPart bodyPart, Entity item);
	void unequip(BodyPart bodyPart);

public:
	void init() override;
	void update(Entity entity) override;
	void update_components() override;




};

