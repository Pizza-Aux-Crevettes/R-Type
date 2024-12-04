/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound.hpp
*/

#pragma once

#include <string>

class Sound {
  public:
    Sound(std::string soundFile = "", int volume = 100);
    ~Sound();
    std::string getSoundFile() const;
    void setSoundFile(std::string soundFile);
    int getVolume() const;
    void setVolume(int volume);

  private:
    std::string _soundFile;
    int _volume;
};
