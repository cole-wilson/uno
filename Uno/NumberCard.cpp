/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* NumberCard.cpp
*
* Represents an NumberCard as a subclass of Card which has an number.
*/

#include "NumberCard.h"

NumberCard::NumberCard(const CARD_COLOR color, int number) {
	this->number = number;
	this->color = color;

	load_texture();
}

std::string NumberCard::to_string() const {
	std::string output = (char)this->color + std::to_string(this->get_number());
	return output;
}

int NumberCard::get_number() const {
	return this->number;
}

CARD_TYPE NumberCard::get_type() const
{
	return NUMBER;
}
