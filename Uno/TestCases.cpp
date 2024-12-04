/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* TestCases.cpp
*
* This test class handles 5 common test cases in the game.
*/

#include "TestCases.h"


void TestCases::testNewGame() {
	// test sending the "new" message to the server and getting a code
	Server server;
	server.new_game();
	if (server.get_join_code() != "") {
		std::cout << "[PASS] testNewGame()" << std::endl;
	}
	else {
		std::cout << "[FAIL] testNewGame()" << std::endl;
	}
}


void TestCases::testJoinGame() {
	Server hostServer;
	hostServer.new_game();
	// ^^ start a new test game

	// check if joining with that code gives player index == 1
	Server joinServer;
	joinServer.join_game(hostServer.get_join_code());
	if (joinServer.get_player_id() == 1) {
		std::cout << "[PASS] testJoinGame()" << std::endl;
	}
	else {
		std::cout << "[FAIL] testJoinGame()" << std::endl;
	}
}

void TestCases::testTurnDataRead() {
	// test deserializing a turndata object from a string
	TurnData td("1\n1\n1\n1\nB0\n");
	bool card_ok = td.get_card()->get_color() == BLUE;
	bool drawn_ok = td.get_cards_drawn() == 1;
	bool next_ok = td.get_next_player() == 1;
	bool hand_ok = td.get_cards_in_hand() == 1;
	bool dir_ok = td.get_direction() == 1;

	if (card_ok && drawn_ok && next_ok && hand_ok && dir_ok) {
		std::cout << "[PASS] testTurnDataRead()" << std::endl;
	}
	else {
		std::cout << "[FAIL] testTurnDataRead()" << std::endl;
	}
}

void TestCases::testTurnDataWrite() {
	// test serializing a turndata object TO a string
	TurnData td(1, 1, 1, 1, new NumberCard(BLUE, 0));
	if (td.to_string() == "1\n1\n1\n1\nB0\n") {
		std::cout << "[PASS] testTurnDataWrite()" << std::endl;
	}
	else {
		std::cout << "[FAIL] testTurnDataWrite()" << std::endl;
	}
}

void TestCases::testDeckFromString() {
	// read a deck from string
	Deck deck("B0");
	if (deck.read_face_up()->get_color() == BLUE) {
		std::cout << "[PASS] testDeckFromString()" << std::endl;
	}
	else {
		std::cout << "[FAIL] testDeckFromString()" << std::endl;
	}
}

void TestCases::runAll()
{
	// run each test sequentially
	testNewGame();
	testJoinGame();
	testTurnDataRead();
	testTurnDataWrite();
	testDeckFromString();
}
