#pragma once
#include "Deck.h"
#include "Server.h"
#include <mutex>
#include <condition_variable>

enum GAME_MODE {
    SELECTING_CARD = 0,
    SELECTING_WILD_COLOR = 1,
    WAITING_FOR_OTHER_PLAYERS = 2,
    MENU = 3
};

class Game {
public:
    Game();

    Deck drawpile;
    Deck discardpile;
    Deck hand;
    int n_players = -1;
    int turn = 0;
    int direction = 1;
    int handindex = 6;

    int* n_cards;

    GAME_MODE mode = MENU;
    int chosen_color = 0;

    std::mutex select_mtx;
    std::condition_variable select_cv;
    bool select_has_selected;

    Server serv;

    void mainloop();

    void release_select();
    void wait_select();



};

