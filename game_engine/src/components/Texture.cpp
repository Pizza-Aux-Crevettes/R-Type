/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Texture.cpp
**
** Represents a texture component with a path to a graphical asset.
** Provides methods to get and set the texture path.
*/

#include "components/Texture.hpp"
#include <iostream>

Texture::Texture(std::string texturePath) : _texturePath(texturePath) {}

std::string Texture::getTexturePath() const {
    return this->_texturePath;
}

void Texture::setTexturePath(std::string texturePath) {
    this->_texturePath = texturePath;
}

void Texture::display() const {
    std::cout << "Texture component displayed!" << std::endl;
}

Texture::~Texture() {}
