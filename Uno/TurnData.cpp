#include "TurnData.h"

TurnData::TurnData(string data)
{
	//Server.split_message();
	vector<string> tokens = Server::split_message(data);

	this->turn_action = (TURN_ACTION)std::stoi(tokens.at(0));

	this->next_player = std::stoi(tokens.at(1));

	if (this->turn_action == PASS || this->turn_action == DRAW_PASS) {
		this->card = nullptr;
	}
	else {
		this->card = card_from_string(tokens.at(2));
	}
	
	this->uno = tokens.at(3) == "uno";

}

TurnData::TurnData(TURN_ACTION t_action, int next_player, bool uno) {
	this->turn_action = t_action;
	this->next_player = next_player;
	this->uno = uno;
	this->card = nullptr;
}

TurnData::TurnData(TURN_ACTION t_action, int next_player, Card* card, bool Uno) {
	this->turn_action = t_action;
	this->next_player = next_player;
	this->uno = uno;
	this->card = card;
}

bool TurnData::is_uno()
{
	return this->uno;
}

int TurnData::get_next_player()
{
	return this->next_player;
}

Card* TurnData::get_card()
{
	return this->card;
}

TURN_ACTION TurnData::get_turn_action()
{
	return this->turn_action;
}

string TurnData::to_string()
{
	string output;
	output += std::to_string(get_turn_action()) + '\n';
	output += std::to_string(get_next_player()) + '\n';
	output += (*card).to_string() + '\n';
	output += uno ? "uno" : "no-uno-yet";
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
