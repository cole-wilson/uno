/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* SoundPlayer.h
*
* This class wraps SFML's sound player functionality into a single
* class for ease of use.
*/

#pragma once
#include <SFML/Audio.hpp>
#include <thread>
#include <string>

class SoundPlayer {
    // the SFML objects needed for sound
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    // an empty constructor just for storing an empty class...
    SoundPlayer() {};

    // make a new sound from filename
    SoundPlayer(std::string filename);

    // actually play sound (in other thread)
    void play();
};

