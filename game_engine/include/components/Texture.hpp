/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Texture.hpp
*/

#pragma once

#include "Components.hpp"
#include <string>

class Texture : public Component {
  public:
    Texture(std::string texturePath = "");
    ~Texture();
    std::string getTexturePath() const;
    void setTexturePath(std::string texturePath);
    bool getIsLoaded() const;
    void setIsLoaded(bool isLoaded);
    sf::Texture& getTexture();
    void setTexture(const sf::Texture& texture);
    void display() const override;

  protected:
  private:
    std::string _texturePath;
    sf::Texture _texture;
    bool _isLoad = false;
};
