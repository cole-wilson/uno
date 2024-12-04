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

    SoundPlayer* uno_sound;
    SoundPlayer* click_sound;
    SoundPlayer* card_sound;

    sf::Texture cardback_texture;
    sf::Sprite drawpile_sprite;

    sf::Font helvetica;
    sf::Text mainmessage;
    sf::Text otherplayers;
    std::string codeInput;
    sf::Color background_color;

    //https://stackoverflow.com/questions/49509687/passing-an-entire-class-as-argument-to-a-thread-c-as-in-c-sharp
    std::thread gamethread;

public:
    GraphicsMain();
    void run();
};

