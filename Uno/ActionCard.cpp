/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* ActionCard.cpp
*
* Represents an ActionCard as a subclass of Card which has an action. This can
* also be an undecided wild card as well. The type is a value of CARD_ACTION enum.
*/

#include "ActionCard.h"

// construct an action card from a color and action type
ActionCard::ActionCard(const CARD_COLOR color, CARD_ACTION action) {
    this->color = color;
    this->action = action;

    // load the card texture from the file
    load_texture();
}

std::string ActionCard::to_string() const
{
    // construct a string from the char enum of the color type
    std::string output{ (char)this->color };

    // add the action char enum char
    output += (char)this->action;
    return output;
}

// getters
CARD_ACTION ActionCard::get_action() const
{
    return this->action;
}

CARD_TYPE ActionCard::get_type() const
{
    return ACTION;
}
