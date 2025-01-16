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

void SoundManager::setEffectSound(const std::string& title, const std::string& soundFile) {
    Sound newSound;
    if (!newSound.getSoundBuffer().loadFromFile(soundFile)) {
        std::cerr << "Error: unable to load the audio file: " << soundFile << std::endl;
        return;
    }
    newSound.getSound().setBuffer(newSound.getSoundBuffer());
    newSound.getSound().setVolume(50);
    newSound.getSound().setLoop(true);
    _gameEffects[title] = std::move(newSound);
}

void SoundManager::setMusicSound(const std::string& title, const std::string& soundFile) {
    Sound newSound;
    if (!newSound.getSoundBuffer().loadFromFile(soundFile)) {
        std::cerr << "Error: unable to load the audio file: " << soundFile << std::endl;
        return;
    }

    newSound.getSound().setBuffer(newSound.getSoundBuffer());
    newSound.getSound().setVolume(50);
    newSound.getSound().setLoop(true);
    _music[title] = std::move(newSound);
}

Sound& SoundManager::getEffectSound(const std::string& key) {
    return _gameEffects[key];
}

Sound& SoundManager::getMusicSound(const std::string& key) {
    return _music[key];
}

void SoundManager::setEffectVolumn(int volume) {
    for (auto& [key, sound] : _gameEffects) {
        sound.setVolumeSound(volume);
    }
}

void SoundManager::setMusicVolumn(int volume) {
    for (auto& [key, sound] : _music) {
        sound.setVolumeSound(volume);
    }
}
