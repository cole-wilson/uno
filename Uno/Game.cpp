#include "Game.h"

Player& Game::nextPlayer()
{
	incrementTurn();
	return this->players.at(turnIndex);
}

void Game::reverseDirection() {
	this->turnDirection *= -1;
}

void Game::incrementTurn(int n) {
	this->turnIndex = (this->turnIndex + (this->turnDirection * n)) % this->players.size();
}

Card& Game::drawCard()
{
	return this->discard.front();
}

Card& Game::getTopDiscard()
{
	return this->discard.back();
}
