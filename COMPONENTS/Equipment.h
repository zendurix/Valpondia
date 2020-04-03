#pragma once

#include <utility>
#include <unordered_map>

#include "../CONFIGURATION.h"


using Entity = std::uint32_t; // to avoid error: error type for Entity. including ECS_config didn't fix this

using eqSlot = std::pair<BodyPart, Entity*>; // pointer, so empty slot can be nullptr


struct Equipment
{

	std::unordered_map<BodyPart, Entity*> eq = 
	{
		{ BodyPart::head, nullptr },
		{ BodyPart::body, nullptr },
		{ BodyPart::hands, nullptr },
		{ BodyPart::legs, nullptr },

		{ BodyPart::lHand, nullptr },
		{ BodyPart::rHand, nullptr }

	};
};