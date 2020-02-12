#pragma once

#include "CONFIGURATION.h"
#include "MapFunctions.h"
#include "Place.h"

class FieldOfView
{
private:
	inline static Vector2D<SharedPtr<Place>>* fieldArr = nullptr;

	FieldOfView() = delete;

	static void update_1qrt(SharedPtr<Place> placeChar);
	static void update_2qrt(SharedPtr<Place> placeChar);
	static void update_3qrt(SharedPtr<Place> placeChar);
	static void update_4qrt(SharedPtr<Place> placeChar);

	static void tracer(SharedPtr<Place> startPoint, float angle, int distance);

	static char set_quarter(float& angle);

	static SharedPtr<Place>  step_tracer(SharedPtr<Place> tracer, char& quarter, char&& dir);

public:

	static void update_view(Vector2D<SharedPtr<Place>> *field, SharedPtr<Place> placeChar);

};


