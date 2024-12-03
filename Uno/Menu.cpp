#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("helvetica.ttf"))
	{
		std::cout << "Font error" << std::endl;
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Host");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (NUMBER_MENU_OPTIONS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setString("Join");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (NUMBER_MENU_OPTIONS + 1) * 2));
	
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (NUMBER_MENU_OPTIONS + 1) * 3));

	selectedItem = 0;
}

Menu::~Menu()
{ }

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_MENU_OPTIONS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < NUMBER_MENU_OPTIONS)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Yellow);
	}
}