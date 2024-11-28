#include "Deck.h"

deque<Card*> Deck::get_all_cards()
{
    return this->cards;
}

Card* Deck::draw_one_card()
{
    Card* card = cards.back();
    cards.pop_back();
    return card;
}

Card* Deck::read_face_up() {
    return cards.front();
}

void Deck::put_face_up(Card* card) {
    cards.push_front(card);
}

Deck::Deck(std::string data) {
    clear_from_string(data);
    this->rng.seed(time(0));
}

Deck::Deck() {
    this->rng.seed(time(0));
}

void Deck::shuffle() {
    // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

    std::shuffle(std::begin(cards), std::end(cards), this->rng);
}

std::string Deck::to_string()
{
    std::string output;
    for (Card* card : this->cards) {
        output += card->to_string() + ',';
    }
    return output;
}

void Deck::clear_from_string(std::string data) {
    this->cards.clear();
    std::vector<std::string> card_strs = Server::split_message(data, ',');
    for (std::string card_str : card_strs) {
        this->put_face_up(TurnData::card_from_string(card_str));
    }
}
