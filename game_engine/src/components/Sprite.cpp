/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite.cpp
**
** The Sprite class represents a graphical object with a texture and size.
** It holds a `texturePath` as a string and `size` as a pair of doubles
** representing the width and height.
** The constructor allows initializing these attributes with default values.
*/

#include "components/Sprite.hpp"
#include <iostream>

/**
 * @brief Constructor for the Sprite component.
 *
 * This constructor initializes the sprite component with the given texture path and size.
 *
 * @param texturePath The path to the texture file for the sprite.
 * @param size The size of the sprite as a pair of width and height.
 */
Sprite::Sprite(std::string texturePath, std::pair<double, double> size)
    : _texturePath(texturePath), _size(size) {}

/**
 * @brief Destructor for the Sprite component.
 *
 * This destructor cleans up any resources used by the sprite component.
 */
Sprite::~Sprite() {}

/**
 * @brief Get the texture file path of the Sprite.
 *
 * This function retrieves the file path of the texture used by the sprite.
 *
 * @return The file path of the texture.
 */
std::string Sprite::getTexturePath() const {
    return this->_texturePath;
}

/**
 * @brief Set the texture file path for the Sprite.
 *
 * This function sets the file path for the texture of the sprite.
 *
 * @param texturePath The new file path for the texture.
 */
void Sprite::setTexturePath(std::string texturePath) {
    this->_texturePath = texturePath;
}

/**
 * @brief Get the size of the Sprite.
 *
 * This function retrieves the size of the sprite as a pair of width and height.
 *
 * @return A pair representing the width and height of the sprite.
 */
std::pair<double, double> Sprite::getSize() const {
    return this->_size;
}

/**
 * @brief Set the size of the Sprite.
 *
 * This function sets the size of the sprite as a pair of width and height.
 *
 * @param size A pair representing the width and height to set for the sprite.
 */
void Sprite::setSize(std::pair<double, double> size) {
    this->_size = size;
}

/**
 * @brief Display the Sprite component information.
 *
 * This function displays a message indicating that the sprite component is being displayed.
 */
void Sprite::display() const {
    std::cout << "Sprite component displayed!" << std::endl;
}