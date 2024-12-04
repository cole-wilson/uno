/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* ActionCard.h
*
* Represents an ActionCard as a subclass of Card which has an action. This can
* also be an undecided wild card as well. The type is a value of CARD_ACTION enum.
*/

#pragma once
#include "Card.h"

/* enum for type of action card */
enum CARD_ACTION {
	SKIP = 's',
	REVERSE = 'r',
	DRAW = 'd',
	WILD_DRAW_FOUR = 'f',
	WILD = 'w'
};


class ActionCard : public Card {
	CARD_ACTION action;
public:
	// constructor
	ActionCard(const CARD_COLOR color, CARD_ACTION action);

	// get string representation of card for server
	std::string to_string() const;

	// get action type
	CARD_ACTION get_action() const;

	// virtual override of get type of card (action)
	CARD_TYPE get_type() const;
};

