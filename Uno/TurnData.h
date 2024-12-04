/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* TurnData.h
*
* This class represents all the data needed to parse a remote turn event,
* including what the player did. This also handles socket serialization of itself.
*/

#pragma once

#include "NumberCard.h"
#include "ActionCard.h"
#include "Server.h"

#include <vector>

using std::string;
using std::vector;


class TurnData {
	// private data members storing the data from each turn
	int cards_drawn;
	int cards_in_hand;
	int next_player;
	int direction;
	Card* card;

public:
	// construct a TurnData object from a string
	TurnData(std::string data);

	// creates a TurnData object from individual parameters
	TurnData(int cards_drawn, int cards_in_hand, int next_player, int direction, Card* card);

	// getters for private data members
	int get_cards_drawn();
	int get_next_player();
	int get_cards_in_hand();
	int get_direction();
	Card* get_card();

	// serializes the TurnData
	string to_string();

	// creates either a Number of Action Card from the string,
	// casts it as a Card, and returns it
	static Card* card_from_string(std::string data);
};

