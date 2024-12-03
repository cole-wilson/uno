#pragma once
#include "Deck.h"
#include "Server.h"

class Game {
public:
    Game();
    Deck drawpile;
    Deck discardpile;
    Deck hand;
    int n_players = -1;
    int turn = 0;
    int direction = 1;

    Server serv;

    void mainloop();



};

