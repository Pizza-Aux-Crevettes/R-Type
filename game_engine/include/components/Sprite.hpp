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
    Sprite();
    ~Sprite();
    std::string getTexturePath() const;
    void setTexturePath(std::string texturePath);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);
    bool getIsLoaded() const;
    void setIsLoaded(bool isLoaded);
    sf::Sprite& getSprite();
    void setSprite(const sf::Sprite& sprite);
    void display() const override;

  private:
    std::string _texturePath;
    std::pair<double, double> _size;
    sf::Sprite _sprite;
    bool _isLoad = false;
};
