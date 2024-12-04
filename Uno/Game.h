/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Game.h
*
* Represents the main gane thread logic of Uno, minus the graphics. This runs a method
* in a seperate thread from the main graphics thread, and communicates with the main thread
* using locks, mutexes, and condition variables. It is a friend of GraphicsMain in order to
* share state across threads. Many variables are not technically thread-safe, although extra
* care has been taking to only read and write to the necessary ones.
*/

#pragma once
#include "Deck.h"
#include "SoundPlayer.h"
#include "Server.h"
#include <mutex>
#include <condition_variable>

enum GAME_MODE {
    SELECTING_CARD = 0,
    SELECTING_WILD_COLOR = 1,
    WAITING_FOR_OTHER_PLAYERS = 2,
    MENU = 3,
    WIN = 4
};

class GraphicsMain;

class Game {
    Deck drawpile;
    Deck discardpile;
    Deck hand;

    GAME_MODE mode = MENU;

    int n_players = -1;
    int turn = 0;
    int direction = 1;
    int handindex = 6;
    int* n_cards;
    int chosen_color = 0;

    std::mutex select_mtx;
    std::condition_variable select_cv;
    bool select_has_selected;

    void release_select();
    void wait_select();

    void mainloop();

public:
    Game();
    Server serv;


    friend GraphicsMain;

};

