/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** SoundManager.hpp
*/

#pragma once

#include <SFML/Window.hpp>
#include "components/Sound.hpp"

class SoundManager {
  public:
    SoundManager();
    ~SoundManager();

    static SoundManager& get();

    void setEffectSound(std::string title, std::string);
    void setMusicSound(std::string title, std::string);
    void setEffectVolumn(int volume);
    void setMusicVolumn(int volume);
    Sound getEffectSound(std::string key);
    Sound getMusicSound(std::string key);

  private:
    std::map<std::string, Sound> _gameEffects;
    std::map<std::string, Sound> _music;
};