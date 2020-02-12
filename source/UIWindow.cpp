#pragma once

#include "pch.h"
#include "UIWindow.h"


UIWindow::UIWindow(int length, int height, int x, int y, MyText titleSet, std::vector<MyText> options,
	int CharSize, bool fit, int outThicc)
	: title(titleSet), choosableContent(options), charSize(CharSize), fitWindow(fit), outlineThicc(outThicc)
{
	addTickBoxes = false;
	if (fitWindow)
		height = (choosableContent.size() * 40 + 40) < height ? (choosableContent.size() * 40 + 40) : height;

	if (choosableContent.size() == 0)
		height = 120;

	height -= outlineThicc;
	length -= outlineThicc;
	x += outlineThicc / 2;
	y += outlineThicc / 2;

	windowBackground = sf::RectangleShape(sf::Vector2f(length, height));
	windowBackground.setFillColor(sf::Color::Black);
	windowBackground.setOutlineColor(sf::Color::Red);
	windowBackground.setOutlineThickness(outlineThicc);
	windowBackground.setPosition(x, y);

	size = choosableContent.size();

	optionsPerPage = height / (charSize + SPACE_BETWEEN_LINES_Y*6);
	showIndexFirst = 0;
	showIndexLast = showIndexFirst + optionsPerPage;

	interactive = true;
}


void UIWindow::add_tickBoxes()
{
	addTickBoxes = true;
	tickBox = sf::RectangleShape(sf::Vector2f(10, 10));
	tickBox.setFillColor(sf::Color::White);
	tickBox.setOutlineColor(MCOL::brown);
	tickBox.setOutlineThickness(3);
}





std::vector<int> UIWindow::call_window_return_choosen_indexes(sf::RenderWindow* win)
{
	std::vector<SharedPtr<Item>> choosen = {};
	chosenIndexes.clear();
	highlightOptionIndex = 0;
	choosed = false;

	while(!choosed)
	{
		show_window(win);
		show_window(win); // to avoid flickering
		if (choosableContent.size() != 0)
		{
			handle_input();
			if (highlightOptionIndex >= showIndexLast)
				scroll_down();
			if (highlightOptionIndex <= showIndexFirst && highlightOptionIndex != 0)
				scroll_up();
		}
		else
		{
			Input::wait_for_input(inputType::space);			
			chosenIndexes.push_back(-1);
			choosed = true;			
		}
	}
	return chosenIndexes;
}




void UIWindow::show_window(sf::RenderWindow* win)
{
	win->draw(windowBackground);

	int x = windowBackground.getPosition().x + 35;
	int y = windowBackground.getPosition().y + 30;

	title.setPosition(x - 10, y - 30);
	title.window_draw(win);

	if (choosableContent.size() != 0)
	{
		for (int i = showIndexFirst; (i < showIndexLast && i < size); i++)
		{
			myText = choosableContent[i];
			myText.setPosition(x, y);

			if (interactive)
				if (i == highlightOptionIndex) 
					myText.set_color_first(sf::Color::Red);

			if (addTickBoxes)
			{
				tickBox.setPosition(x - 20, y + 18);

				if (std::find(chosenIndexes.begin(), chosenIndexes.end(), i) != chosenIndexes.end())
					tickBox.setFillColor(sf::Color::Red);
				else tickBox.setFillColor(sf::Color::White);

				win->draw(tickBox);
			}

			myText.window_draw(win);

			y += CHAR_SIZE + SPACE_BETWEEN_LINES_Y;

		}
	}
	else
	{
		myText = strCol("NOTHING HERE \n press space to exit", MCOL::slatGrey);
		myText.setPosition(x, y);
		myText.window_draw(win);
	}
	win->display();
}





void UIWindow::handle_input()
{
	sleep_for_milliseconds(150);
	char input = Input::user_input_key();
	if (!interactive)
		while (input != STD_ESC)
			input = Input::user_input_key();

	switch (input)
	{
	case  '8':		highlightOptionIndex--;		break;
	case  '2':		highlightOptionIndex++;		break;
	case  ' ':
	{
		if (addTickBoxes)
		{
			if (std::find(chosenIndexes.begin(), chosenIndexes.end(), highlightOptionIndex) == chosenIndexes.end())
				chosenIndexes.push_back(highlightOptionIndex);
			else
				chosenIndexes.erase(std::find(chosenIndexes.begin(), chosenIndexes.end(), highlightOptionIndex));
		}
		break;
	}
	case '\t': // take all
	{
		if (addTickBoxes)
		{
			chosenIndexes.clear();
			for (int i = 0; i < size; i++)
				chosenIndexes.push_back(i);
			choosed = true;
		}
		break;
	}
	case '\n':	
		if (addTickBoxes)
		{
			choosed = true;		
		}
		else
		{
			chosenIndexes.push_back(highlightOptionIndex);
			choosed = true;
		}
		break;
	case STD_ESC:
		if (addTickBoxes)
			chosenIndexes.clear();
		else
			chosenIndexes.push_back(-1);
		choosed = true;
		break;

	default:			break;
	}

	highlightOptionIndex = (highlightOptionIndex == -1) ? 0 : 
		((highlightOptionIndex == size) ? size - 1 : highlightOptionIndex);
}




void UIWindow::scroll_down()
{
	showIndexFirst = highlightOptionIndex - 1;
	showIndexLast = (showIndexLast + optionsPerPage) > size ? size : showIndexLast + optionsPerPage - 1;
}
void UIWindow::scroll_up()
{
	showIndexLast = highlightOptionIndex + 1;
	showIndexFirst = (showIndexLast - optionsPerPage) < 0 ? 0 : (showIndexLast - optionsPerPage);
}