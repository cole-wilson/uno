#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(std::string filename)
{
	if (!buffer.loadFromFile(filename)) {}
	sound.setBuffer(buffer);
}

void SoundPlayer::play()
{
	sound.play();
}
