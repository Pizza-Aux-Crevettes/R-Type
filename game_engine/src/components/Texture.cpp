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

/**
 * @brief Constructor for the Texture component.
 *
 * This constructor initializes the texture component with the given texture
 * file path.
 *
 * @param texturePath The path to the texture file.
 */
Texture::Texture(std::string texturePath, std::vector<int> textureRect)
    : _texturePath(texturePath), _textureRect(textureRect) {}

/**
 * @brief Get the texture file path.
 *
 * This function retrieves the file path of the texture.
 *
 * @return The file path of the texture.
 */
std::string Texture::getTexturePath() const {
    return this->_texturePath;
}

/**
 * @brief Set the texture file path.
 *
 * This function sets the file path for the texture.
 *
 * @param texturePath The new file path for the texture.
 */
void Texture::setTexturePath(std::string texturePath) {
    this->_texturePath = texturePath;
}

std::vector<int> Texture::getTextureRect() const {
    return this->_textureRect;
}

bool Texture::getIsLoaded() const {
    return this->_isLoad;
}

void Texture::setIsLoaded(const bool isLoaded) {
    this->_isLoad = isLoaded;
}

sf::Texture& Texture::getTexture() {
    return this->_texture;
}

void Texture::setTexture(const sf::Texture& texture) {
    this->_texture = texture;
}

/**
 * @brief Display the Texture component information.
 *
 * This function displays a message indicating that the texture component is
 * being displayed.
 */
void Texture::display() const {
    std::cout << "Texture component displayed!" << std::endl;
}

/**
 * @brief Destructor for the Texture component.
 *
 * This destructor cleans up any resources used by the texture component.
 */
Texture::~Texture() {}
