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
	std::string filepath = "cards/" + to_string() + ".png";
	if (!texture.loadFromFile(filepath))
	{
		throw 1;
	}
	setTexture(texture);
}
