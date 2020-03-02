#pragma once

#include "MyText.h"


class UIWindow
{
private:
	inline static const int WIN_OUTLINE_THICC = 4;
	inline static const int SPACE_BETWEEN_LINES_Y = 3;

	sf::RectangleShape windowBackground;
	std::vector<MyText> choosableContent;
	std::vector<int> chosenIndexes;

	int size;
	int highlightOptionIndex;
	MyText title;
	MyText myText;

	bool interactive;
	bool fitWindow;
	bool addTickBoxes;
	sf::RectangleShape tickBox;

	bool choosed;

	int outlineThicc;

	// for scrolling
	int optionsPerPage;
	int showIndexFirst;
	int showIndexLast;
	int charSize;


	// private functions
	void show_window(sf::RenderWindow* win);
	void handle_input();
	void scroll_down();
	void scroll_up();

public:
	UIWindow(int length, int height, int x, int y, MyText titleSet, std::vector<MyText> options, int CharSize,
		bool fit = true, int outThicc = WIN_OUTLINE_THICC);
	inline ~UIWindow() {};


	std::vector<int> call_window_return_choosen_indexes(sf::RenderWindow* win);

	void add_tickBoxes();
	inline void set_interactive(bool set) { interactive = set; }



};
