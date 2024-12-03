#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#define NUMBER_MENU_OPTIONS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int PressedItem() { return selectedItem; }

private:
	int selectedItem;
	sf::Font font;
	sf::Text menu[NUMBER_MENU_OPTIONS];
};