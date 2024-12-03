#include "TurnData.h"

TurnData::TurnData(string data)
{
	//Server.split_message();
	vector<string> tokens = Server::split_message(data);

	this->cards_drawn = std::stoi(tokens.at(0));
	this->cards_in_hand = std::stoi(tokens.at(1));
	this->next_player = std::stoi(tokens.at(2));
	this->direction = std::stoi(tokens.at(3));

	if (tokens.at(3) == "no_card") {
		this->card = nullptr;
	}
	else {
		this->card = card_from_string(tokens.at(4));
	}
}

TurnData::TurnData(int cards_drawn, int cards_in_hand, int next_player, int direction, Card* card) {
	this->cards_drawn = cards_drawn;
	this->cards_in_hand = cards_in_hand;
	this->next_player = next_player;
	this->direction = direction;
	this->card = card;
}

int TurnData::get_cards_drawn()
{
	return this->cards_drawn;
}

int TurnData::get_next_player()
{
	return this->next_player;
}

int TurnData::get_cards_in_hand()
{
	return this->cards_in_hand;
}

int TurnData::get_direction()
{
	return this->direction;
}

Card* TurnData::get_card()
{
	return this->card;
}


string TurnData::to_string()
{
	string output;
	output += std::to_string(get_cards_drawn()) + '\n';
	output += std::to_string(get_cards_in_hand()) + '\n';
	output += std::to_string(get_next_player()) + '\n';
	output += std::to_string(get_direction()) + '\n';
	if (this->card == nullptr) {
		output += "no_card\n";
	}
	else {
		output += (*card).to_string() + '\n';
	}
	return output;
}

Card* TurnData::card_from_string(std::string data)
{
	Card* card;
	CARD_COLOR card_color = (CARD_COLOR)data[0];
	char card_type = data[1];
	if (card_type <= '9' && card_type >= '0') {
		card = new NumberCard(card_color, card_type - '0');
	}
	else {
		card = new ActionCard(card_color, (CARD_ACTION)card_type);
	}
	return card;
}
