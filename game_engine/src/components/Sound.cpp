/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound.cpp
**
** The Sound class represents a sound component for an entity in the game.
** It holds a file path to the sound and the volume level for playback.
** The constructor allows initializing the sound with a given file and volume.
*/

#include "components/Sound.hpp"

Sound::Sound(std::string soundFile, int volume) : _soundFile(soundFile), _volume(volume)
{
}

Sound::~Sound()
{
}

std::string Sound::getSoundFile() const
{
    return this->_soundFile;
}

void Sound::setSoundFile(std::string soundFile)
{
    this->_soundFile = soundFile;
}

int Sound::getVolume() const
{
    return this->_volume;
}

void Sound::setVolume(int volume)
{
    this->_volume = volume;
}
