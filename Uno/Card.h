/*
* Uno - CPT_S 122 Final Project
* 
* Cole Wilson and Shane Ganz
* 
* Card.h
* 
* Represents a generic Card (of either Action or Number type, which is implemented
* in the subclasses). Every Card has a color. It is also implemented as a subclass of
* sf::Sprite, so that we can draw the card objects on the window.
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

enum CARD_COLOR {
	BLUE = 'B',
	GREEN = 'G',
	RED = 'R',
	YELLOW = 'Y',
	WILD_CARD = 'W'
};

enum CARD_TYPE {
	NUMBER = 0,
	ACTION = 1,
	NONE = 2
};

class ActionCard;
class NumberCard;

class Card : public sf::Sprite {
	sf::Texture texture;

protected:
	CARD_COLOR color;
	void load_texture();
public:
	CARD_COLOR get_color() const;
	virtual std::string to_string() const;
	virtual CARD_TYPE get_type() const;
};

