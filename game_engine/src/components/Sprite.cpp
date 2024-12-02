/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite.cpp
**
** The Sprite class represents a graphical object with a texture and size.
** It holds a `texturePath` as a string and `size` as a vector of two doubles
*representing the width and height.
** The constructor allows initializing these attributes with default values.
*/

#include "components/Sprite.hpp"

Sprite::Sprite(std::string texturePath, std::vector<double> size)
    : _texturePath(texturePath), _size(size) {}

Sprite::~Sprite() {}

std::string Sprite::getTexturePath() const {
    return this->_texturePath;
}

void Sprite::setTexturePath(std::string texturePath) {
    this->_texturePath = texturePath;
}

std::vector<double> Sprite::getSize() const {
    return this->_size;
}

void Sprite::setSize(std::vector<double> size) {
    this->_size = size;
}
