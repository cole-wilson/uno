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
