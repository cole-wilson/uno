#pragma once
#include <SFML/Audio.hpp>
#include <thread>
#include <string>

class SoundPlayer {
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    SoundPlayer(std::string filename);
    void play();
};

