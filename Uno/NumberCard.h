/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* NumberCard.h
*
* Represents an NumberCard as a subclass of Card which has an number.
*/

#pragma once
#include "Card.h"
class NumberCard : public Card {
	// the number of the card
	int number;
public:
	// constructor
	NumberCard(const CARD_COLOR color, int number);

	// serialize card to string
	std::string to_string() const;

	// getter
	int get_number() const;

	// override virtual to return NUMBER
	CARD_TYPE get_type() const;
};

