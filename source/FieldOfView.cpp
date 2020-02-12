#include "pch.h"
#include "FieldOfView.h"




void FieldOfView::update_view(Vector2D<SharedPtr<Place>> *field, SharedPtr<Place> placeChar)
{
	fieldArr = field;
	std::thread qrt1(update_1qrt, placeChar);
	std::thread qrt2(update_2qrt, placeChar);
	std::thread qrt3(update_3qrt, placeChar);
	std::thread qrt4(update_4qrt, placeChar);

	qrt1.join();
	qrt2.join();
	qrt3.join();
	qrt4.join(); 
}


void FieldOfView::update_1qrt(SharedPtr<Place>  placeChar)
{
	for (float alpha = 0.0f; alpha < 90.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, placeChar->get_characterHere()->get_view());
}
void FieldOfView::update_2qrt(SharedPtr<Place>  placeChar)
{
	for (float alpha = 90.0f; alpha < 180.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, placeChar->get_characterHere()->get_view());
}
void FieldOfView::update_3qrt(SharedPtr<Place>  placeChar)
{
	for (float alpha = 180.0f; alpha < 270.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, placeChar->get_characterHere()->get_view());
}
void FieldOfView::update_4qrt(SharedPtr<Place>  placeChar)
{
	for (float alpha = 270.0f; alpha < 360.0f; alpha += DEGREE_STEP)
		tracer(placeChar, alpha, placeChar->get_characterHere()->get_view());
}













void FieldOfView::tracer(SharedPtr<Place>  startPoint, float angle, int distance) // void (*operation)())
{
	SharedPtr<Place>  tracer = startPoint;
	char quarter = set_quarter(angle);	
	angle *= (PI / 180.0f);  //degree to radian
	float bAdd = tan(angle) * ACCURACY;
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

	while (!tracer->get_isObstacle() && stepCounter <= distance)
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
	}
	tracer->make_visible();





}










char FieldOfView::set_quarter(float& angle)
{
	if (are_same_float(angle, 0.0f) || (angle > 0.0f && angle < 90.0f ))
	{
		return 1;
	}
	if (are_same_float(angle, 90.0f) || (angle > 90.0f && angle < 180.0f))
	{
		angle -= 90.0f;
		return 2;
	}
	if (are_same_float(angle, 180.0f) || (angle > 180.0f && angle < 270.0f))
	{
		angle -= 180.0f;
		return 3;
	}
	if (are_same_float(angle, 270.0f) || (angle > 270.0f && angle < 360.0f))
	{
		angle -= 270.0f;
		return 4;
	}
}









SharedPtr<Place>  FieldOfView::step_tracer(SharedPtr<Place>  tracer, char& quarter, char&& dir)
{// '|' vertical  '-' horizontal   '/' diagonally
	switch (quarter)
	{
	case 1:
		tracer = (dir == '|') ? (*fieldArr)[tracer->get_y() - 1][tracer->get_x()] : 
				((dir == '-') ?	(*fieldArr)[tracer->get_y()][tracer->get_x() + 1] : 
				/*dir == '/'*/	(*fieldArr)[tracer->get_y() - 1][tracer->get_x() + 1]);
		break;
	case 2:
		tracer = (dir == '|') ? (*fieldArr)[tracer->get_y() + 1][tracer->get_x()] :
				((dir == '-') ? (*fieldArr)[tracer->get_y()][tracer->get_x() + 1] :
				/*dir == '/'*/  (*fieldArr)[tracer->get_y() + 1][tracer->get_x() + 1]);
		break;
	case 3:
		tracer = (dir == '|') ? (*fieldArr)[tracer->get_y() + 1][tracer->get_x()] :
				((dir == '-') ? (*fieldArr)[tracer->get_y()][tracer->get_x() - 1] :
				/*dir == '/'*/	(*fieldArr)[tracer->get_y() + 1][tracer->get_x() - 1]);
		break;
	case 4:
		tracer = (dir == '|') ? (*fieldArr)[tracer->get_y() - 1][tracer->get_x()] :
				((dir == '-') ? (*fieldArr)[tracer->get_y()][tracer->get_x() - 1] :
				/*dir == '/'*/	(*fieldArr)[tracer->get_y() - 1][tracer->get_x() - 1]);
		break;
	}
	tracer->make_visible();
	return tracer;
}

