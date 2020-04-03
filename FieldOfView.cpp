#include "pch.h"
#include "FieldOfView.h"

#include "MAP_GEN/map_functions.h"
#include "general_purpose_func.h"
#include "Place.h"


bool FieldOfView::tracer_point_to_point(SharedPtr<Place> start, SharedPtr<Place> end, void(*action)(SharedPtr<Place>))
{
	int x1 = start->get_x();	int y1 = start->get_y();
	int x2 = end->get_x();		int y2 = end->get_y();

	double aSide = abs(x1 - x2);
	double bSide = abs(y1 - y2);
	double cSide = sqrt(aSide*aSide + bSide *bSide);

	double a = 0.0, b = 0.0;

	double angle = 0;
	///////////////////// NOT FINISHED
}





void FieldOfView::update_view(Vector2D<SharedPtr<Place>> *field, SharedPtr<Place> placeChar, int viewDistance)
{
	fieldArr = field;

	if (!initialized)
	{
		std::thread qrt1(update_1qrt, placeChar, viewDistance);
		qrt1.join();
		initialized = true;
	}


	std::thread qrt1(update_1qrt, placeChar, viewDistance);
	std::thread qrt2(update_2qrt, placeChar, viewDistance);
	std::thread qrt3(update_3qrt, placeChar, viewDistance);
	std::thread qrt4(update_4qrt, placeChar, viewDistance);

	qrt1.join();
	qrt2.join();
	qrt3.join();
	qrt4.join();

}

void FieldOfView::update_1qrt(SharedPtr<Place> placeChar, int viewDistance)
{
	for (float alpha = 0.0f; alpha < 90.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, viewDistance);
}
void FieldOfView::update_2qrt(SharedPtr<Place>  placeChar, int viewDistance)
{
	for (float alpha = 90.0f; alpha < 180.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, viewDistance);
}
void FieldOfView::update_3qrt(SharedPtr<Place>  placeChar, int viewDistance)
{
	for (float alpha = 180.0f; alpha < 270.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, viewDistance);
}
void FieldOfView::update_4qrt(SharedPtr<Place>  placeChar, int viewDistance)
{
	for (float alpha = 270.0f; alpha < 360.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, viewDistance);
}













void FieldOfView::tracer(SharedPtr<Place>  startPoint, float angle, int distance) 
{
	SharedPtr<Place> tracer = startPoint;
	char quarter = set_quarter(angle);
	float bAdd;

	if (!initialized)
	{
		float angleRad = deg_to_rad(angle);
		angleToYstep[angle] = tan(angleRad) * ACCURACY;
	}
	bAdd = angleToYstep[angle];


	float b = 0.0f;
	float a = 0.0f;
	float counterA = a;
	float counterB = b;

	int stepCounter = 0;

	if (are_same_float(angle, 0.0f) || are_same_float(angle, 180.0f))
	{
		while (!tracer->get_isObstacle() && stepCounter <= distance)
		{
			tracer = step_tracer(tracer, quarter, '|');
			stepCounter++;
			if (tracer->get_x() == 0 || tracer->get_x() == MYLENGTH - 1 ||
				tracer->get_y() == 0 || tracer->get_y() == MYHEIGHT - 1)
				break;
		}
	}

	while (!tracer->get_isObstacle())
	{
		a += ACCURACY;
		b += bAdd;
		counterA += ACCURACY;
		counterB += bAdd;

		if (are_same_float(counterA, 1.0f) && (are_same_float(counterB, 1.0f) || counterB > 1.0f))
		{
			counterB -= 1.0f;
			counterA = 0.0f;
			tracer = step_tracer(tracer, quarter, '/');
			stepCounter += 2;
		}
		else if (are_same_float(counterB, 1.0f) || counterB > 1.0f)
		{
			counterB -= 1.0f;
			tracer = step_tracer(tracer, quarter, '|');
			stepCounter++;
		}
		else if (are_same_float(counterA, 1.0f))
		{
			counterA = 0.0f;
			tracer = step_tracer(tracer, quarter, '-');
			stepCounter++;
		}

		if (tracer->get_x() == 0 || tracer->get_x() == MYLENGTH - 1 ||
			tracer->get_y() == 0 || tracer->get_y() == MYHEIGHT - 1)
			break;

		if (stepCounter >= distance)
			if (distance_meter(*tracer, *startPoint) >= distance)
				break;


	}
	tracer->make_visible();
}










char FieldOfView::set_quarter(float& angle)
{
	if ((angle > 0.0f && angle < 90.0f) || are_same_float(angle, 0.0f))
	{
		return 1;
	}
	if ((angle > 90.0f && angle < 180.0f) || are_same_float(angle, 90.0f))
	{
		angle -= 90.0f;
		return 2;
	}
	if ((angle > 180.0f && angle < 270.0f) || are_same_float(angle, 180.0f))
	{
		angle -= 180.0f;
		return 3;
	}
	if ((angle > 270.0f && angle < 360.0f) || are_same_float(angle, 270.0f))
	{
		angle -= 270.0f;
		return 4;
	}
}









SharedPtr<Place>  FieldOfView::step_tracer(SharedPtr<Place>  tracer, char& quarter, char&& dir)
{// '|' vertical  '-' horizontal   '/' diagonally
	int x, y;
	switch (quarter)
	{
	case 1:
		if		(dir == '|')	{ y = -1; x = 0; }
		else if (dir == '-')	{ y =  0; x = 1; }
		else	/*dir == '/'*/  { y = -1; x = 1; }
		break;
	case 2:
		if		(dir == '|')	{ y =  1; x = 0; }
		else if (dir == '-')	{ y =  0; x = 1; }
		else	/*dir == '/'*/	{ y =  1; x = 1; }
		break;
	case 3:
		if		(dir == '|')	{ y = 1; x =  0; }
		else if (dir == '-')	{ y = 0; x = -1; }
		else	/*dir == '/'*/	{ y = 1; x = -1; }
		break;
	case 4:
		if		(dir == '|')	{ y = -1; x =  0; }
		else if (dir == '-')	{ y =  0; x = -1; }
		else	/*dir == '/'*/	{ y = -1; x = -1; }
		break;
	}
	tracer = (*fieldArr)[tracer->get_y() + y][tracer->get_x() + x];
	tracer->make_visible();
	return tracer;
}





float FieldOfView::deg_to_rad(float deg)
{
	return deg * (PI / 180.0f);
}
