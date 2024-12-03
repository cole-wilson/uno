#pragma once

#include <string>
#include <SFML/Graphics.hpp>

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

class Card : public sf::Sprite {
	sf::Texture texture;

protected:
	CARD_COLOR color;
	void load_texture();
public:
	CARD_COLOR get_color() const;
	virtual std::string to_string() const;
	virtual CARD_TYPE get_type() const;
};

