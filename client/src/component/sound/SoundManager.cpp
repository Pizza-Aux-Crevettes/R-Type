/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** SoundManager.cpp
*/

#include "component/sound/SoundManager.hpp"
#include "components/Sound.hpp"
#include <iostream>

SoundManager::SoundManager() {};

SoundManager::~SoundManager() = default;

SoundManager& SoundManager::get() {
    static SoundManager instance;   
    return instance;
}

void SoundManager::setEffectSound(std::string title, std::string soundFile) {
    auto newSound = Sound();
    if (!newSound.getSoundBuffer().loadFromFile(soundFile)) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
    }
    newSound.getSound().setBuffer(newSound.getSoundBuffer());
    newSound.getSound().setLoop(true);
    std::cout << "Create Sound " << title << std::endl;
    _gameEffects[title] = newSound;
}

void SoundManager::setMusicSound(std::string title, std::string soundFile) {
    auto newSound = Sound();
    if (!newSound.getSoundBuffer().loadFromFile(soundFile)) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
    }
    newSound.getSound().setBuffer(newSound.getSoundBuffer());
    std::cout << "Create Sound " << title << std::endl;
    _music[title] = newSound;
}

Sound SoundManager::getEffectSound(std::string key) {
    std::cout << "Get Sound " << key << std::endl;
    return _gameEffects[key];
}

Sound SoundManager::getMusicSound(std::string key) {
    std::cout << "Get Sound " << key << std::endl;
    return _music[key];
}

void SoundManager::setEffectVolumn(int volume) {
    for (auto& [key, sound] : _gameEffects) {
        std::cout << "Key: " << key << std::endl;
        sound.setVolume(volume);
    }
}

void SoundManager::setMusicVolumn(int volume) {
    for (auto& [key, sound] : _music) {
        std::cout << "Key: " << key << std::endl;
        sound.setVolume(volume);
    }
}
