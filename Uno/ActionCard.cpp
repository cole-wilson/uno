#include "ActionCard.h"

ActionCard::ActionCard(const CARD_COLOR color, CARD_ACTION action) {
    this->color = color;
    this->action = action;
}

std::string ActionCard::to_string() const
{
    std::string output{ (char)this->color };
    output += (char)this->action;
    return output;
}

CARD_ACTION ActionCard::get_action() const
{
    return this->action;
}
