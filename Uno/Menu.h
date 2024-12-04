#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Game.h"

//set number of items on the main menu, makes operations more readable
#define NUMBER_MENU_OPTIONS 3

//enum for the different submenus, as well as when waiting for host to begin game
enum MENU_STATE {
	INITIAL_STATE = 0,
	HOST_STATE = 1,
	JOIN_STATE = 2,
	WAITING_STATE = 3
};

class Menu
{
public:
	//menu state default
	MENU_STATE menu_state = INITIAL_STATE;
	//constructor of variable size
	Menu(float width, float height);
	//destructor
	~Menu();

	//draws the appropriate content based on enum
	void draw(sf::RenderWindow& window);
	//controls, which edit selectedItem and change the color to mark the choice
	void MoveUp();
	void MoveDown();
	//returns selectedItem to denote what the user chose
	int PressedItem();
	//specific function to be run when host is selected, uses the current game object as parameter
	void HostPressed(Game& game);
	//stores the user's join code as they enter it
	void CodeStore(Game& game, string code);

private:
	//numbered menu 
	int selectedItem;
	//font
	sf::Font font;
	//array of text for all the menu options
	sf::Text menu[NUMBER_MENU_OPTIONS];
	//text
	sf::Text hostmessage;
	sf::Text joinmessage;
	sf::Text waitingmessage;
	//logo sprite and texture from file
	sf::Texture logo_texture;
	sf::Sprite logo_sprite;
};