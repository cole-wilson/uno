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

// the current state of the game and graphics
enum GAME_MODE {
    SELECTING_CARD = 0,
    SELECTING_WILD_COLOR = 1,
    WAITING_FOR_OTHER_PLAYERS = 2,
    MENU = 3,
    WIN = 4
};

// forward declaration of GraphicsMain to use as friend
class GraphicsMain;

class Game {
    // flag to quit thread
    bool quit = false;

    // the decks/hands used
    Deck drawpile;
    Deck discardpile;
    Deck hand;

    // the current game mode
    GAME_MODE mode = MENU;

    // number of players in game
    int n_players = -1;
    int turn = 0; // the current player id whos turn it is
    int direction = 1; // the direction of play (-1 or 1)
    int handindex = 6; // the index of the card being chosen by the player in their hand
    int* n_cards; // an array of integers storing the # cards per player
    int chosen_color = 0; // a placeholder for communication between threads for wild card choice

    // mutexes and locks for cross-thread waiting (see implementations)
    std::mutex select_mtx;
    std::condition_variable select_cv;
    bool select_has_selected;

    // ^^ see implementations for explanations
    void release_select();
    void wait_select();

    // the main loop of the game logic (non graphics) to run in a thread
    void mainloop();

public:
    // constructor
    Game();

    // method to set quit flag thread
    void quit_thread();

    // the server object
    // (public for global access, just here so in namespace scope...)
    Server serv;

    // allow GraphicsMain to edit
    friend GraphicsMain;
};

