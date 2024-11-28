#pragma once
#include "Card.h"

enum CARD_ACTION {
	SKIP = 's',
	REVERSE = 'r',
	DRAW = 'd',
	WILD_ACTION = 'w'
};

class ActionCard : public Card {
	CARD_ACTION action;
public:
	ActionCard(const CARD_COLOR color, CARD_ACTION action);
	std::string to_string() const;
	CARD_ACTION get_action() const;
};

