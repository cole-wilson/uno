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
public:
	void testNewGame();
	void testJoinGame();
	void testTurnDataRead();
	void testTurnDataWrite();
	void testDeckFromString();

	void runAll();
};

