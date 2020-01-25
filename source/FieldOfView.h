#pragma once

#include "CONFIGURATION.h"
#include "general_purpose_func.h"
#include "MapFunctions.h"
#include "Place.h"
#include "Character.h"
#include "GAME.h"


class FieldOfView
{
private:
	FieldOfView() = delete;

	static void update_1qrt(std::shared_ptr<Place> placeChar);
	static void update_2qrt(std::shared_ptr<Place> placeChar);
	static void update_3qrt(std::shared_ptr<Place> placeChar);
	static void update_4qrt(std::shared_ptr<Place> placeChar);

	static void tracer(std::shared_ptr<Place> startPoint, float angle, int distance);

	static char set_quarter(float& angle);

	static std::shared_ptr<Place>  step_tracer(std::shared_ptr<Place> tracer, char& quarter, char&& dir);

public:
	static void update_view(std::shared_ptr<Place> placeChar);
};


