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

/* store the card color and the corresponding serialization char */
enum CARD_COLOR {
	BLUE = 'B',
	GREEN = 'G',
	RED = 'R',
	YELLOW = 'Y',
	WILD_CARD = 'W'
};

/* store the card type */
enum CARD_TYPE {
	NUMBER = 0,
	ACTION = 1,
	NONE = 2
};

class Card : public sf::Sprite {
	// the texture of the playing card (image)
	sf::Texture texture;

protected:
	CARD_COLOR color;
	// called in constructors
	void load_texture();
public:
	// get the color of the card
	// different than inherited getColor()!
	CARD_COLOR get_color() const;

	// pure virtual to_string method for serialization
	virtual std::string to_string() const;

	// get the type of card (CARD_TYPE)
	virtual CARD_TYPE get_type() const;
};

