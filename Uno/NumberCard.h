#pragma once
#include "Card.h"
class NumberCard : public Card {
	int number;
public:
	NumberCard(const CARD_COLOR color, int number);
	std::string to_string() const;
	int get_number() const;
};

