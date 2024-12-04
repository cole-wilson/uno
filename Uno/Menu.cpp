/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Menu.cpp
*
* Handles the entrypoint menu for the game where the user can
* choose different options.
*/

#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("helvetica.ttf"))
	{
		std::cerr << "Font error" << std::endl;
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Host\n(use arrows)");
	menu[0].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 1.3));
	menu[0].setStyle(sf::Text::Bold | sf::Text::Underlined);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setString("Join");
	menu[1].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 1.9));
	menu[1].setStyle(sf::Text::Bold | sf::Text::Underlined);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 2.5));
	menu[2].setStyle(sf::Text::Bold | sf::Text::Underlined);

	hostmessage.setFont(font);
	hostmessage.setFillColor(sf::Color::Yellow);
	hostmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) * 1));
	hostmessage.setStyle(sf::Text::Bold);

	joinmessage.setFont(font);
	joinmessage.setFillColor(sf::Color::Yellow);
	joinmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) *  1));
	joinmessage.setStyle(sf::Text::Bold);

	waitingmessage.setFont(font);
	waitingmessage.setFillColor(sf::Color::Yellow);
	waitingmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) * 1));
	waitingmessage.setStyle(sf::Text::Bold);

	if (!logo_texture.loadFromFile("unologo.png")) {}
	logo_sprite = sf::Sprite(logo_texture);
	logo_sprite.setPosition(sf::Vector2f((width / 2) - (330 / 2), 10));
	selectedItem = 0;
}

Menu::~Menu()
{ }

void Menu::draw(sf::RenderWindow& window)
{
	switch (menu_state)
	{
	case INITIAL_STATE:
		window.draw(logo_sprite);
		for (int i = 0; i < NUMBER_MENU_OPTIONS; i++)
		{
			window.draw(menu[i]);
		}
		break;
	case HOST_STATE:
		window.draw(hostmessage);
			break;
	case JOIN_STATE:
		window.draw(joinmessage);
		break;
	case WAITING_STATE:
		waitingmessage.setString("Waiting for host...");
		window.draw(waitingmessage);
		break;
	}
	
	
}

void Menu::MoveUp()
{
	if ((selectedItem - 1) >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if ((selectedItem + 1) < NUMBER_MENU_OPTIONS)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Yellow);
	}
}

void Menu::HostPressed(Game& game)
{
	game.serv.new_game();
	menu_state = HOST_STATE;
	hostmessage.setString(" Join Code: " + game.serv.get_join_code() + " \n\nPress enter when ready...");
}

void Menu::CodeStore(Game& game, string codeInput)
{
	joinmessage.setString("      Enter code:\n\n[ " + codeInput + " ]\n\nPress enter when ready...");
}



