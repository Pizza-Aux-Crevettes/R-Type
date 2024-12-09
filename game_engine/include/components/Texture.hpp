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
    void display() const override;

  protected:
  private:
    std::string _texturePath;
};
