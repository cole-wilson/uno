/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Card.cpp
*
* Represents a generic Card (of either Action or Number type, which is implemented
* in the subclasses). Every Card has a color. It is also implemented as a subclass of
* sf::Sprite, so that we can draw the card objects on the window.
*/

#include "Card.h"


// getter
CARD_COLOR Card::get_color() const {
    return this->color;
}

// unused, virtual function overridden in the subclasses
std::string Card::to_string() const {
    return "" + ((char)this->color);
}

// getter
CARD_TYPE Card::get_type() const
{
    return NONE;
}

// load the texture file from the cards/ directory
void Card::load_texture() {
	// if card is a real card
	if (to_string() != "no") {
		std::string filepath = "cards/" + to_string() + ".png";
		if (!texture.loadFromFile(filepath))
		{
			throw 1;
		}
		// use the inherited setTexture() from sf::Sprite
		setTexture(texture);
	}
}
