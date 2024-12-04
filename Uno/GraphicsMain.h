/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* GraphicsMain.h
*
* Represents the main graphics thread of Uno, minus the game logic. This runs a method
* in a seperate thread from the logic thread, and communicates with it
* using locks, mutexes, and condition variables. The main event loop and SFML window
* handling is all encapsulated within this class.
*/

#pragma once

#include "Deck.h"
#include "Game.h"
#include "NumberCard.h"
#include "ActionCard.h"
#include "Menu.h"
#include "Server.h"
#include "SoundPlayer.h"

class GraphicsMain {
    Game game;

    // the three sounds used in the game
    SoundPlayer* uno_sound;
    SoundPlayer* click_sound;
    SoundPlayer* card_sound;

    // the draw pile sprite/texture
    // because it's the back of a card it's not a Card in and of itself so just a sprite
    sf::Texture cardback_texture;
    sf::Sprite drawpile_sprite;

    // the font used across graphics
    sf::Font helvetica;

    // different text messages on the screen
    sf::Text mainmessage; // generic main message reused across many modes
    sf::Text otherplayers; // show list of all players and their card counts

    std::string codeInput; // stores input of join code
    sf::Color background_color; // the background color of the screen

    // the thread of the game logic loop
    // empty here because we don't want to start it just yet
    // see https://stackoverflow.com/questions/49509687/passing-an-entire-class-as-argument-to-a-thread-c-as-in-c-sharp
    std::thread gamethread;

public:
    // constructor
    GraphicsMain();

    // main entrypoint
    void run();
};

