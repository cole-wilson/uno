#pragma once

//#define SERVER_ADDRESS "uno.cole.ws"
#define SERVER_ADDRESS "192.168.0.103"
#define SERVER_PORT 9999


#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

using std::string;
using std::vector;

class Server {
	std::string join_code;
	sf::TcpSocket socket;
	int player_id;

public:
	Server();
	~Server();

	void send(const std::string data);
	std::string recv();

	void new_game();
	void join_game(std::string join_code);

	int get_player_id() const;
	std::string get_join_code() const;

	static std::vector<std::string> split_message(std::string data, char delim='\n');
};