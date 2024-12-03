#pragma once
#include "Deck.h"
#include "Server.h"
#include <mutex>
#include <condition_variable>

enum GAME_MODE {
    SELECTING_CARD = 0,
    SELECTING_WILD_COLOR = 1,
    WAITING_FOR_OTHER_PLAYER = 2,
    JOIN_MENU = 3
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

    GAME_MODE mode = JOIN_MENU;
    int chosen_color = 0;

    std::mutex select_mtx;
    std::condition_variable select_cv;
    bool select_has_selected;

    Server serv;

    void mainloop();

    void release_select();
    void wait_select();



};

