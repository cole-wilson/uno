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


CARD_COLOR Card::get_color() const {
    return this->color;
}

std::string Card::to_string() const {
    return "" + ((char)this->color);
}

CARD_TYPE Card::get_type() const
{
    return NONE;
}

void Card::load_texture() {
	if (to_string() != "no") {
		std::string filepath = "cards/" + to_string() + ".png";
		if (!texture.loadFromFile(filepath))
		{
			throw 1;
		}
		setTexture(texture);
	}
}
