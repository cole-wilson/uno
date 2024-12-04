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
	int number;
public:
	NumberCard(const CARD_COLOR color, int number);
	std::string to_string() const;
	int get_number() const;
	CARD_TYPE get_type() const;
};

