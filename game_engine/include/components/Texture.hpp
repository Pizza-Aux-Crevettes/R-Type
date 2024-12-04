/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Texture.hpp
*/

#pragma once

#include <string>

class Texture {
  public:
    Texture(std::string texturePath = "");
    ~Texture();
    std::string getTexturePath() const;
    void setTexturePath(std::string texturePath);

  protected:
  private:
    std::string _texturePath;
};
