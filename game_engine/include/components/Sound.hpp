/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound.hpp
*/

#pragma once

#include "Components.hpp"
#include <SFML/Audio.hpp>
#include <string>

class Sound : public Component {
  public:
    Sound(std::string soundFile = "", int volume = 100);
    ~Sound();
    std::string getSoundFile() const;
    void setSoundFile(std::string soundFile);
    int getVolume() const;
    void setVolume(int volume);
    void display() const override;

  private:
    std::string _soundFile;
    int _volume;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool _isLoad = false;
};
