/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Server.h
*
* Handles communication with the Uno server hosted on an Oracle Ubuntu VPS instance.
* This handles interactions with other clients through the server, and uses sockets to
* communicate and serialize data.
*/

#pragma once

// the main production server:
#define SERVER_ADDRESS "uno.cole.ws"

// for debugging, Cole's mac on a local tailnet instance
//#define SERVER_ADDRESS "mac.net.cole.ws"

// the TCP port used by the server
#define SERVER_PORT 9999


#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

using std::string;
using std::vector;

class Server {
	// the code used to join the game
	std::string join_code;

	// the SFML socket object
	sf::TcpSocket socket;

	// the id of the current player
	int player_id;

public:
	// constructor and destructor
	Server();
	~Server();

	// send a string across the socket
	void send(const std::string data);

	// get a string across from the socket (blocks)
	std::string recv();

	// get a new random join code from the server and start hosting
	// a new game
	void new_game();

	// start the game once everyone has joined
	// with given draw pile string
	// returns # of players
	int start_game(std::string drawpilestring);

	// join a game that has already been created using join code
	// returns the success of the join
	bool join_game(std::string join_code);

	// getters
	int get_player_id() const;
	std::string get_join_code() const;

	// a STATIC method designed to help split data using delimiters
	static std::vector<std::string> split_message(std::string data, char delim='\n');
};
