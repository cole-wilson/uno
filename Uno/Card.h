#pragma once

#include <string>

enum CARD_COLOR {
	BLUE = 'B',
	GREEN = 'G',
	RED = 'R',
	YELLOW = 'Y',
	WILD_CARD = 'W'
};

enum CARD_TYPE {
	NUMBER = 0,
	ACTION = 1,
	NONE = 2
};

class ActionCard;
class NumberCard;

class Card {
protected:
	CARD_COLOR color;
public:
	CARD_COLOR get_color() const;
	virtual std::string to_string() const;
	virtual CARD_TYPE get_type() const;
};

