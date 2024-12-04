/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Deck.h
*
* Represents a deck of cards (or a player's hand). This is implemented by wrapping
* the STL deque class (like a vector but front and back operations supported) and providing
* easy-to-use methods for it. It also handles server serialization and decoding of a deck.
*/

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
	// construct a deck from a serialized string (B0,B1,B2,etc.)
	Deck(std::string data);

	// empty deck
	Deck();

	// shuffle the deck
	void shuffle();

	// get a reference to the internal deque object
	deque<Card*>& get_all_cards();

	// draw one card from the top of the face down deck,
	// removing it from deck
	Card* draw_one_card();

	// draw one card and remove from deck at given index
	Card* draw_one_card(int index);

	// draw and immediately discard one card without looking
	// from top of dace down deck
	void burn_one_card();

	// peek at the face up card on deck without removing
	Card* read_face_up();

	// put a card face up on deck
	void put_face_up(Card* card);

	// get # cards in deck.hand
	int size() const;
	
	// serialize into string for server
	std::string to_string();

	// clear deck and replace with contents of serialized server string
	void clear_from_string(std::string data);
};

