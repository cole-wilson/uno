#include "Player.h"

Player::~Player() {
}

Player::Player() {
}

std::string Player::getName()
{
	return this->mName;
}

std::vector<Card>& Player::getHand()
{
	return this->mHand;
}

sf::IpAddress Player::getAddress()
{
	return this->mAddress;
}

void Player::setName(std::string name) {
	this->mName = name;
}

void Player::setAddress(sf::IpAddress address) {
	this->mAddress = address;
}

void Player::turn()
{
	//g.drawCard();
}
