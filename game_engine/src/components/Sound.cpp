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
#include <iostream>

/**
 * @brief Constructor for the Sound component.
 *
 * This constructor initializes the sound component with the given sound file
 * and volume.
 *
 * @param soundFile The path to the sound file.
 * @param volume The volume level for the sound (typically between 0 and 100).
 */
Sound::Sound(std::string soundFile, int volume)
    : _soundFile(soundFile), _volume(volume) {}

/**
 * @brief Destructor for the Sound component.
 *
 * This destructor cleans up any resources used by the sound component.
 */
Sound::~Sound() {}

/**
 * @brief Get the sound file path.
 *
 * This function retrieves the path to the sound file used by the sound
 * component.
 *
 * @return The path to the sound file.
 */
std::string Sound::getSoundFile() const {
    return this->_soundFile;
}

/**
 * @brief Set the sound file path.
 *
 * This function sets the path to the sound file for the sound component.
 *
 * @param soundFile The new path to the sound file.
 */
void Sound::setSoundFile(std::string soundFile) {
    this->_soundFile = soundFile;
}

/**
 * @brief Get the volume level.
 *
 * This function retrieves the current volume level of the sound component.
 *
 * @return The volume level of the sound.
 */
int Sound::getVolume() const {
    return this->_volume;
}

/**
 * @brief Set the volume level.
 *
 * This function sets the volume level for the sound component.
 *
 * @param volume The new volume level to set (typically between 0 and 100).
 */
void Sound::setVolume(int volume) {
    this->_volume = volume;
}

/**
 * @brief Display the Sound component information.
 *
 * This function displays a message indicating that the sound component is being
 * displayed.
 */
void Sound::display() const {
    std::cout << "Sound component displayed!" << std::endl;
}