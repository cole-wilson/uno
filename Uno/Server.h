#pragma once

//#define SERVER_ADDRESS "uno.cole.ws"
#define SERVER_ADDRESS "192.168.0.107"
#define SERVER_PORT 9999


#include <iostream>
#include <string>
#include <SFML/Network.hpp>

class Server {
	std::string join_code;
	sf::TcpSocket socket;
	int player_id;

	void send(const std::string data);
	std::string recv();

public:
	Server();
	Server(std::string join_code);
	~Server();

	int get_player_id() const;
	std::string get_join_code() const;
};

//sf::TcpSocket socket;
//sf::Socket::Status status = socket.connect("192.168.0.107", 9999);
//if (status != sf::Socket::Done)
//{
//	std::cout << status << std::endl;
//}
//
//char data[] = "new";
//
//char code[6];
//std::size_t received;
//
//
//socket.send(data, sizeof(data) - 1);
//socket.receive(code, 6, received);
//
//std::cout << "join code " << code << std::endl;