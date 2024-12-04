#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Game.h"

#define NUMBER_MENU_OPTIONS 3

enum MENU_STATE {
	INITIAL_STATE = 0,
	HOST_STATE = 1,
	JOIN_STATE = 2,
	WAITING_STATE = 3
};

class Menu
{
public:
	MENU_STATE menu_state = INITIAL_STATE;
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int PressedItem() { return selectedItem; }
	void HostPressed(Game& game);
	void CodeStore(Game& game, string code);

private:
	int selectedItem;
	sf::Font font;
	sf::Text menu[NUMBER_MENU_OPTIONS];
	sf::Text hostmessage;
	sf::Text joinmessage;
};