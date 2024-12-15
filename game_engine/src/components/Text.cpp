/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text.cpp
**
** The Text class represents a text object with a string attribute.
** It holds the text content in a `std::string` and provides methods to get and
** set the text.
** The constructor allows initializing the text, with a default empty string.
*/

#include "components/Text.hpp"
#include <iostream>

/**
 * @brief Constructor for the Text component.
 *
 * This constructor initializes the text component with the given text value.
 *
 * @param text The initial text for the component.
 */
Text::Text(std::string text, std::string filename, unsigned int characterSize)
    : _initText(text), _fontFile(filename), _charSize(characterSize) {}

/**
 * @brief Destructor for the Text component.
 *
 * This destructor cleans up any resources used by the text component.
 */
Text::~Text() {}

/**
 * @brief Get the text of the Text component.
 *
 * This function retrieves the current text of the component.
 *
 * @return The current text of the component.
 */
std::string Text::getString() const {
    return this->_initText;
}

/**
 * @brief Set the text of the Text component.
 *
 * This function sets a new text value for the component.
 *
 * @param text The new text to be set.
 */
void Text::setString(std::string text) {
    this->_initText = text;
}

sf::Font& Text::getFont() {
    return this->_font;
}

unsigned int Text::getCharacterSize() const {
    return this->_charSize;
}

bool Text::getIsLoaded() const {
    return this->_isLoad;
}

std::string Text::getFontFile() const {
    return this->_fontFile;
}

void Text::setIsLoaded(bool isLoaded) {
    this->_isLoad = isLoaded;
}

sf::Text& Text::getText() {
    return this->_text;
}

/**
 * @brief Display the Text component information.
 *
 * This function displays a message indicating that the text component is being
 * displayed.
 */
void Text::display() const {
    std::cout << "Text component displayed!" << std::endl;
}