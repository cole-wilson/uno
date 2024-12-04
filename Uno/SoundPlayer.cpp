/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* SoundPlayer.cpp
*
* This class wraps SFML's sound player functionality into a single
* class for ease of use.
*/

#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(std::string filename)
{
	// load the sound file (.wav normally) from filesystem
	if (!buffer.loadFromFile(filename)) {}

	// set audio buffer to the sound
	sound.setBuffer(buffer);
}

void SoundPlayer::play()
{
	// play the sound
	sound.play();
}
