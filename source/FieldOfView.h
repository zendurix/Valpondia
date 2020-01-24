#pragma once

#include "CONFIGURATION.h"
#include "general_purpose_func.h"
#include "MapFunctions.h"
#include "Place.h"
#include "Character.h"
#include "GAME.h"



void update_view(std::shared_ptr<Place>  placeChar);

void update_1qrt(std::shared_ptr<Place>  placeChar);
void update_2qrt(std::shared_ptr<Place>  placeChar);
void update_3qrt(std::shared_ptr<Place>  placeChar);
void update_4qrt(std::shared_ptr<Place>  placeChar);

void tracer(std::shared_ptr<Place>  startPoint, float angle, int distance);

char set_quarter(float& angle);

std::shared_ptr<Place>  step_tracer(std::shared_ptr<Place>  tracer, char& quarter, char&& dir);
