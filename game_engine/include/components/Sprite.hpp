/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite.hpp
*/

#pragma once

#include "Components.hpp"
#include <string>
#include <vector>

class Sprite : public Component {
  public:
    Sprite(std::string texturePath = "",
           std::pair<double, double> size = {0.0, 0.0});
    ~Sprite();
    std::string getTexturePath() const;
    void setTexturePath(std::string texturePath);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);
    void display() const override;

  private:
    std::string _texturePath;
    std::pair<double, double> _size;
};
