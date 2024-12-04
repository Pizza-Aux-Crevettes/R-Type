/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Texture.hpp
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

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

#endif /* !TEXTURE_HPP_ */
