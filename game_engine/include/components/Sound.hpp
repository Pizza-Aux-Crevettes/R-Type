/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound.hpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include "Components.hpp"

class Sound : public Component {
  public:
    Sound(std::string soundFile = "");
    ~Sound();
    static Sound& get();
    sf::Sound& getSound();
    sf::SoundBuffer& getSoundBuffer();
    std::string getSoundFile() const;
    void setSoundFile(std::string soundFile);
    int getVolume() const;
    void setVolume(int volume);
    void display() const override;

  private:
    std::string _soundFile;
    int _volume;
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    bool _isLoad = false;
};
