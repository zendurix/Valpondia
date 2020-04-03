#pragma once

#include "CONFIGURATION.h"

class Place;

class FieldOfView
{
private:
	inline static Vector2D<SharedPtr<Place>>* fieldArr = nullptr;
	
	inline static std::unordered_map<float, float> angleToYstep;

	inline static bool initialized = false;


	FieldOfView() = delete;

	static void update_1qrt(SharedPtr<Place> placeChar, int viewDistance);
	static void update_2qrt(SharedPtr<Place> placeChar, int viewDistance);
	static void update_3qrt(SharedPtr<Place> placeChar, int viewDistance);
	static void update_4qrt(SharedPtr<Place> placeChar, int viewDistance);

	static void tracer(SharedPtr<Place> startPoint, float angle, int distance);

	static char set_quarter(float& angle);

	static SharedPtr<Place>  step_tracer(SharedPtr<Place> tracer, char& quarter, char&& dir);

	static float deg_to_rad(float deg);

public:

	static void update_view(Vector2D<SharedPtr<Place>> *field, SharedPtr<Place> placeChar, int viewDistance);

	static bool tracer_point_to_point(SharedPtr<Place> start, SharedPtr<Place> end, void(*action)(SharedPtr<Place>) = nullptr);

};


