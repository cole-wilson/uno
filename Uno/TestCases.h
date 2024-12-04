/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* TestCases.h
*
* This test class handles 5 common test cases in the game.
*/

#pragma once

#include "Deck.h"
#include "TurnData.h"
#include "Server.h"
#include "NumberCard.h"

#include <iostream>

class TestCases {
	// tests the server new game functionality
	void testNewGame();

	// tests the join game functionality of server
	void testJoinGame();

	// tests reading a TurnData object from string
	void testTurnDataRead();
	
	// tests writing a TurnData object to a string
	void testTurnDataWrite();

	// tests reading a deck from a string
	void testDeckFromString();

public:
	// run all of the tests
	void runAll();
};

