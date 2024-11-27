#pragma once

#include "Card.h"
#include "Player.h"
#include <vector>

using std::vector;

class Game {
	vector<Card> drawpile;
	vector<Card> discard;
	vector<Player> players;

	int turnDirection = 1;
	int turnIndex = 0;

public:
	Player& nextPlayer();
	void reverseDirection();
	void incrementTurn(int n = 1);
	Card& drawCard();
	Card& getTopDiscard();
};

