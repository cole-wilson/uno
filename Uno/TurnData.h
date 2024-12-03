#pragma once

#include "NumberCard.h"
#include "ActionCard.h"
#include "Server.h"

#include <vector>

using std::string;
using std::vector;


class TurnData {
	int cards_drawn;
	int cards_in_hand;
	int next_player;
	int direction;
	Card* card;

public:
	TurnData(std::string data);
	TurnData(int cards_drawn, int cards_in_hand, int next_player, int direction, Card* card);

	int get_cards_drawn();
	int get_next_player();
	int get_cards_in_hand();
	int get_direction();
	Card* get_card();

	string to_string();

	static Card* card_from_string(std::string data);
};
