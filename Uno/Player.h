#pragma once

#include "Card.h"

#include <vector>
#include <string>
#include <SFML/Network.hpp>

class Player {
	std::string mName;
	std::vector<Card> mHand;
	sf::IpAddress mAddress;

public:
	~Player();
	Player();

	std::string getName();
	std::vector<Card>& getHand();
	sf::IpAddress getAddress();

	void setName(std::string name);
	void setAddress(sf::IpAddress mAddress);

	void turn();
};

