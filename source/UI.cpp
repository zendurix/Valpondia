#include "pch.h"
#include "UI.h"

#include "general_purpose_func.h"

int UI::center_text_posX(sf::Text text, int centeringLength)
{
	int charLength = get_char_length(text);
	int size = text.getString().getSize();
	int posX = centeringLength / 2 - (size / 2) * (charLength + 1);
	return posX;
}
int UI::center_text_posX(MyText text, int centeringLength)
{
	int charLength = text.get_charLength();
	int size = text.get_string().size();
	int posX = centeringLength / 2 - (size / 2) * (charLength + 1);
	return posX;
}

int UI::center_text_posY(sf::Text text, int centeringHeight)
{
	int charHeight = get_char_height(text);
	int posY = centeringHeight / 2 - (charHeight / 2);
	return posY;
}

void UI::init_UI(sf::RenderWindow* win, Character* playerChar)
{
	if (!initialized)
	{
		initialized = true;

		window = win;
		player = playerChar;

		smallBlackWin = sf::RectangleShape(sf::Vector2f(500, 300));
		smallBlackWin.setFillColor(sf::Color::Black);
		smallBlackWin.setOutlineColor(sf::Color::Blue);
		smallBlackWin.setOutlineThickness(4);
		smallBlackWin.setPosition(100, 100);


		bodyPartBlackWin = sf::RectangleShape(sf::Vector2f(600, BODY_PARTS_COUNT * (CHAR_SIZE+10)));
		bodyPartBlackWin.setFillColor(sf::Color::Black);
		bodyPartBlackWin.setOutlineColor(sf::Color::Blue);
		bodyPartBlackWin.setOutlineThickness(4);
		bodyPartBlackWin.setPosition(100, 100);


		int fullWinOutThick = 8;
		fullBlackWin = sf::RectangleShape(sf::Vector2f(WIN_LENGTH - fullWinOutThick * 2, WIN_HEIGHT - fullWinOutThick * 2));
		fullBlackWin.setFillColor(sf::Color::Black);
		fullBlackWin.setOutlineColor(sf::Color::Green);
		fullBlackWin.setOutlineThickness(fullWinOutThick);
		fullBlackWin.setPosition(fullWinOutThick, fullWinOutThick);

		tickBox = sf::RectangleShape(sf::Vector2f(10, 10));
		tickBox.setFillColor(sf::Color::White);
		tickBox.setOutlineColor(MCOL::brown);
		tickBox.setOutlineThickness(3);
		
		blackWin = smallBlackWin;


		init_texts();
	}
}


void UI::init_texts()
{
	text = init_text();
	myText = MyText(strCol("", COL::White), 32, 0, 0, MyText::get_STD_FONT());
	invTitle = MyText(strCol("INVENTORY", COL::Yellow), 32, 0, 0, MyText::get_STD_FONT());


}

std::vector<SharedPtr<Item>> UI::pick_items_window(std::vector<SharedPtr<Item>>* itemToChoose)
{
	bool choosed = false;
	int highlightOpt = 0;
	int size = itemToChoose->size();
	char input;
	std::vector<SharedPtr<Item>> choosen = {};
	int height = itemToChoose->size() * 40 + 40;

	while(!choosed)
	{

		blackWin.setSize(sf::Vector2f(blackWin.getSize().x, height));
		window->draw(blackWin);

		int x = blackWin.getPosition().x + 35;
		int y = blackWin.getPosition().y + 30;



		for (int i = 0; i < size; i++)
		{
			myText = (*itemToChoose)[i]->get_name();
			myText.setPosition(x, y);

			if (i == highlightOpt) myText.set_color_first(sf::Color::Yellow);
			else				   myText.set_color_first((*itemToChoose)[i]->get_name().get_color_first());


			tickBox.setPosition(x - 20, y + 18);

			if (std::find(choosen.begin(), choosen.end(), (*itemToChoose)[i]) != choosen.end())
				 tickBox.setFillColor(sf::Color::Yellow);
			else tickBox.setFillColor(sf::Color::White);

			window->draw(tickBox);
			myText.window_draw(window);

			y += CHAR_SIZE + 3;

		}
		window->display();

		sleep_for_milliseconds(150);
		input = user_input_key();
		switch (input)
		{
		case  '8':		highlightOpt--;		break;
		case  '2':		highlightOpt++;		break;
		case  ' ':	
		{
			if (std::find(choosen.begin(), choosen.end(), (*itemToChoose)[highlightOpt]) == choosen.end())
				choosen.push_back((*itemToChoose)[highlightOpt]); 
			else
				choosen.erase(std::find(choosen.begin(), choosen.end(), (*itemToChoose)[highlightOpt]));
			break;
		}
		case '\t': // take all
		{
			for (int i = 0; i < size; i++)
			{
				if (std::find(choosen.begin(), choosen.end(), (*itemToChoose)[i]) == choosen.end())
					choosen.push_back((*itemToChoose)[i]);
				else
					;				
			}
			choosed = true;
			break;
		}
		case '\n':		choosed = true;		break;
		case STD_ESC:
			choosed = true;
			choosen.clear();
			break;

		default :			break;
		}

		highlightOpt = (highlightOpt == -1) ? 0 : ((highlightOpt == size) ? size - 1 : highlightOpt);
	}
	return choosen;
}















void UI::player_inventory_window()
{
	bool exit = false;
	char input;
	int highlightOpt = 0;

	std::vector< SharedPtr<Item>>* inv = player->get_inventory_ref();

	while (!exit)
	{
		window->draw(fullBlackWin);		
		
		int centX = center_text_posX(invTitle);
		invTitle.setPosition(centX, 20);
		invTitle.window_draw(window);

		int x = 30;
		int y = 50;
		int size = inv->size();

		for (int i = 0; i < size; i++)
		{
			myText = (*inv)[i]->get_name();
			myText.setPosition(x, y);

			if (i == highlightOpt) myText.set_color_first(sf::Color::Yellow);
			else				   myText.set_color_first((*inv)[i]->get_name().get_color_first());

			myText.window_draw(window);
			y += CHAR_SIZE;
		}
			   		 	     	 	  	  	   	

		window->display();


		input = user_input_key();

		switch (input)
		{
		case STD_ESC:
			exit = true;
			break;
		case '8':
			highlightOpt--;
			break;
		case '2':
			highlightOpt++;
			break;
		case '\n':
		{
			window->draw(fullBlackWin);

			int centX = center_text_posX(invTitle);
			invTitle.setPosition(centX, 20);
			invTitle.window_draw(window);

			x = 30;
			y = 50;
			for (int i = 0; i < size; i++)
			{
				myText = (*inv)[i]->get_name();
				myText.setPosition(x, y);

				if (i == highlightOpt) myText.set_color_first(sf::Color::Yellow);
				else				   myText.set_color_first((*inv)[i]->get_name().get_color_first());

				myText.window_draw(window);
				y += CHAR_SIZE;
			}
			window->display();
			item_options_window((*inv)[highlightOpt]);
			if (inv->size() < size)
				size--;
			window->display();
		}
			break;
		default:
			break;
					   			 
		}
		
		highlightOpt = (highlightOpt == -1) ? (size - 1) : ((highlightOpt == size) ? 0 : highlightOpt);
		sleep_for_milliseconds(150);

	}

}





void UI::item_options_window(SharedPtr<Item> item)
{
	std::string options[3] = { "look", "drop" };
	options[2] = item->get_isWorn() ? "unequip" : "equip";
	int size = 3;

	char input;
	int highlightOpt = 0;
	bool exit = false;

	int x = 420;
	int y = 340;


	smallBlackWin.setPosition(400, 300);

	while (!exit)
	{
		sleep_for_milliseconds(150);
		x = 420;
		y = 380;

		window->draw(smallBlackWin);
		myText = item->get_name();
		myText.setPosition(410, 310);
		myText.window_draw(window);
		for (int i = 0; i < size; i++)
		{
			text->setPosition(x, y);
			text->setString(options[i]);

			if (i == highlightOpt) text->setFillColor(sf::Color::Yellow);
			else				   text->setFillColor(sf::Color::White);

			window->draw(*text);
			y += CHAR_SIZE;
		}
		window->display();


		input = user_input_key();

		switch (input)
		{
		case STD_ESC:
			exit = true;
			break;
		case '8':
			highlightOpt--;
			break;
		case '2':
			highlightOpt++;
			break;
		case '\n':
		{
			if (options[highlightOpt] == "look")
				; // info about obj
			else if (options[highlightOpt] == "drop")
				player->drop_item(item);
			else if (options[highlightOpt] == "equip")
			{
				BodyPart bodypart = pick_bodyPart(item->get_bodyPart());
				player->equip_item(item, bodypart); 
			}
			else if (options[highlightOpt] == "unequip")
				; ////
			exit = true;
		}
			break;
		default:
			break;

		}


		highlightOpt = (highlightOpt == -1) ? (size - 1) : ((highlightOpt == size) ? 0 : highlightOpt);
	}


}



BodyPart UI::pick_bodyPart(BodyPart bodypart)
{
	std::string options[BODY_PARTS_COUNT] = { "head   ", "body   ", "hands  ", "legs   ", "rHand  ", "lHand  " };
	int size = BODY_PARTS_COUNT;

	SharedPtr<Item>* eq = player->get_equipped_ref();
	BodyPart ret;

	char input;
	int highlightOpt = (bodypart == BodyPart::forHands) ? (int)BodyPart::lHand : (int)bodypart;
	bool exit = false;

	int x;
	int y;

	bodyPartBlackWin.setPosition(400, 300);

	while (!exit)
	{
		sleep_for_milliseconds(150);
		x = 420;
		y = 320;

		window->draw(bodyPartBlackWin);
		for (int i = 0; i < size; i++)
		{
			myText.clear();
			myText.setPosition(x, y);
			myText += strCol(options[i], COL::White);
			myText += (eq[i]) ? eq[i]->get_name() : strCol("none ", MCOL::grey);

			if (i == highlightOpt)				
			{
				myText.set_color_first(sf::Color::Yellow);
			}
			else if ((BodyPart)i == bodypart || (bodypart == BodyPart::forHands && 
				((BodyPart)i == BodyPart::rHand || (BodyPart)i == BodyPart::lHand)))
			{
				myText.set_color_first(sf::Color::White);
			}
			else
			{
				myText.set_color_first(MCOL::grey);
			}
			myText.window_draw(window);
			y += CHAR_SIZE;
		}
		window->display();


		input = user_input_key();

		switch (input)
		{
		case '8':
			highlightOpt--;
			while (!((BodyPart)highlightOpt == bodypart || (bodypart == BodyPart::forHands &&
				((BodyPart)highlightOpt == BodyPart::rHand || (BodyPart)highlightOpt == BodyPart::lHand))))
			{
				highlightOpt--;
				highlightOpt = (highlightOpt == -1) ? (size - 1) : ((highlightOpt == size) ? 0 : highlightOpt);
			}
			break;
		case '2':
			highlightOpt++;
			highlightOpt = (highlightOpt == -1) ? (size - 1) : ((highlightOpt == size) ? 0 : highlightOpt);
			while (!((BodyPart)highlightOpt == bodypart || (bodypart == BodyPart::forHands &&
				((BodyPart)highlightOpt == BodyPart::rHand || (BodyPart)highlightOpt == BodyPart::lHand))))
			{
				highlightOpt++;
				highlightOpt = (highlightOpt == -1) ? (size - 1) : ((highlightOpt == size) ? 0 : highlightOpt);
			}
			break;
		case '\n':
		{
			return (BodyPart)highlightOpt;
		}
		break;
		default:
			break;
		}
	}

}