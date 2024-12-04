#include "Menu.h"
#include <iostream>

//constructor
Menu::Menu(float width, float height)
{
	//loads font and checks for error
	if (!font.loadFromFile("helvetica.ttf")) 
	{
		std::cerr << "Font error" << std::endl;
	}
	//creating the three main menu options
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow); //first one is yellow as that's the default selection
	menu[0].setString("Host"); //giving the text its string content
	menu[0].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 1.3)); //these specific values are mainly trial and error to get something that looks good. Based on dividing into thirds
	menu[0].setStyle(sf::Text::Bold | sf::Text::Underlined); //style options

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red); //red for the unselected options initially
	menu[1].setString("Join");
	menu[1].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 1.9));
	menu[1].setStyle(sf::Text::Bold | sf::Text::Underlined);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2.1, height / (NUMBER_MENU_OPTIONS + 1) * 2.5));
	menu[2].setStyle(sf::Text::Bold | sf::Text::Underlined);

	//text to display when the user selects host. No setstring here because it's changed dynamically in HostPressed
	hostmessage.setFont(font);
	hostmessage.setFillColor(sf::Color::Yellow);
	hostmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) * 1));
	hostmessage.setStyle(sf::Text::Bold);
		
	//join selection text, also no setstring because it needs to display what the user types as they do
	joinmessage.setFont(font);
	joinmessage.setFillColor(sf::Color::Yellow);
	joinmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) *  1));
	joinmessage.setStyle(sf::Text::Bold);

	//text to display before the host starts the game
	waitingmessage.setFont(font);
	waitingmessage.setFillColor(sf::Color::Yellow);
	waitingmessage.setString("Waiting for host...");
	waitingmessage.setPosition(sf::Vector2f(width / 2.7, height / (NUMBER_MENU_OPTIONS + 1) * 1));
	waitingmessage.setStyle(sf::Text::Bold);

	//making sure the texture loads
	if (!logo_texture.loadFromFile("unologo.png"))
	{
		std::cerr << "Logo error" << std::endl;
	}
	logo_sprite = sf::Sprite(logo_texture); //applying the texture to the blank sprite
	logo_sprite.setPosition(sf::Vector2f((width / 2) - (330 / 2), 10));

	selectedItem = 0; //starting the menu at the default position of 0
}

//destructor
Menu::~Menu() 
{ }

//draws the menu items based on the current submenu (menu state)
void Menu::draw(sf::RenderWindow& window)
{
	switch (menu_state)
	{
	case INITIAL_STATE:
		window.draw(logo_sprite); //first puts the logo at the top
		for (int i = 0; i < NUMBER_MENU_OPTIONS; i++) 
		{
			window.draw(menu[i]); //then loop prints all the text in the menu array
		}
		break;
	case HOST_STATE:
		window.draw(hostmessage);
			break;
	case JOIN_STATE:
		window.draw(joinmessage);
		break;
	case WAITING_STATE:
		window.draw(waitingmessage);
		break;
	}
	
	
}

//controls
void Menu::MoveUp()
{
	if ((selectedItem - 1) >= 0)  //keeps the selection from going off screen
	{
		menu[selectedItem].setFillColor(sf::Color::Red); //"deselects" the current option by color
		selectedItem--; //moves to desired item
		menu[selectedItem].setFillColor(sf::Color::Yellow); //"selects" by making it yellow
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

//gets the current selectedItem
int Menu::PressedItem() 
{
	return selectedItem;
}

//special case for when the host item is selected
void Menu::HostPressed(Game& game)
{
	game.serv.new_game(); //tells the server to start a new game
	menu_state = HOST_STATE; //updates the menu state
	hostmessage.setString(" Join Code: " + game.serv.get_join_code() + " \n\nPress enter when ready..."); ////gets the generated join code and prints it to the screen
}

//updates joinmessage to display to the user what they've typed.
void Menu::CodeStore(Game& game, string codeInput) 
{
	joinmessage.setString("      Enter code:\n\n[ " + codeInput + " ]\n\nPress enter when ready...");
}



