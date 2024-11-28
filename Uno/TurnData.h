#pragma once

#include "NumberCard.h"
#include "ActionCard.h"
#include "Server.h"


#include <vector>

using std::string;
using std::vector;

enum TURN_ACTION {
	DRAW_PASS = 0,
	DRAW_PLAY = 1,
	PASS = 2,
	PLAY = 3,
	WIN = 4
};

class TurnData {
	TURN_ACTION turn_action;
	int next_player;
	Card* card;
	bool uno;

public:
	TurnData(std::string data);
	TurnData(TURN_ACTION t_action, int next_player, bool uno);
	TurnData(TURN_ACTION t_action, int next_player, Card* card, bool Uno);

	bool is_uno();
	int get_next_player();
	Card* get_card();
	TURN_ACTION get_turn_action();

	string to_string();

	static Card* card_from_string(std::string data);
};

