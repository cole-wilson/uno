#pragma once

#include "Card.h"
#include "Server.h"
#include "TurnData.h"

#include <deque>
#include <random>
#include <algorithm>

using std::deque;

class Deck {
	deque<Card*> cards;
	std::default_random_engine rng;

public:
	Deck(std::string data);
	Deck();

	void shuffle();

	deque<Card*>& get_all_cards();
	Card* draw_one_card();
	Card* draw_one_card(int index);
	void burn_one_card();
	Card* read_face_up();
	void put_face_up(Card* card);

	int size() const;
	

	std::string to_string();

	void clear_from_string(std::string data);
};

