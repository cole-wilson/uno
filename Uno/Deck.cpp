/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Deck.cpp
*
* Represents a deck of cards (or a player's hand). This is implemented by wrapping
* the STL deque class (like a vector but front and back operations supported) and providing
* easy-to-use methods for it. It also handles server serialization and decoding of a deck.
*/
#include "Deck.h"

// return reference
deque<Card*>& Deck::get_all_cards()
{
    return this->cards;
}

// return back of card deck and remove
Card* Deck::draw_one_card()
{
    Card* card = cards.back();
    cards.pop_back();
    return card;
}

// return given index and remove
Card* Deck::draw_one_card(int index)
{
    Card* card = cards.at(index);
    cards.erase(cards.begin() + index);
    return card;
}

// remove one card and ignore
void Deck::burn_one_card() {
    cards.pop_back();
}

// read the face up
Card* Deck::read_face_up() {
    return cards.front();
}

// put a card face up
void Deck::put_face_up(Card* card) {
    cards.push_front(card);
}

// getter
int Deck::size() const
{
    return this->cards.size();
}

// construct from string and seed RNG
Deck::Deck(std::string data) {
    clear_from_string(data);
    this->rng.seed(time(0));
}

// seed RNG
Deck::Deck() {
    this->rng.seed(time(0));
}

// shuffle the deck using seeded RNG
void Deck::shuffle() {
    // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

    std::shuffle(std::begin(cards), std::end(cards), this->rng);
}


// serialize the deck to a string
std::string Deck::to_string()
{
    std::string output;
    for (Card* card : this->cards) {
        // add each card's string
        output += card->to_string() + ',';
    }
    return output;
}

void Deck::clear_from_string(std::string data) {
    this->cards.clear(); // clear deck

    // add each card after splitting text
    std::vector<std::string> card_strs = Server::split_message(data, ',');
    for (std::string card_str : card_strs) {
        this->cards.push_back(TurnData::card_from_string(card_str));
    }
}
