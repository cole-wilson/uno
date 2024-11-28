#pragma once

#include <string>

enum CARD_COLOR {
	BLUE = 'B',
	GREEN = 'G',
	RED = 'R',
	YELLOW = 'Y',
	WILD = 'W'
};

class ActionCard;
class NumberCard;

class Card {
protected:
	CARD_COLOR color;
public:
	CARD_COLOR get_color() const;
	virtual std::string to_string() const;
};

