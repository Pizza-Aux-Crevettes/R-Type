/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite.hpp
*/

#pragma once

#include <string>
#include <vector>

class Sprite {
  public:
    Sprite(std::string texturePath = "",
           std::pair<double, double> size = {0.0, 0.0});
    ~Sprite();
    std::string getTexturePath() const;
    void setTexturePath(std::string texturePath);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);

  private:
    std::string _texturePath;
    std::pair<double, double> _size;
};
