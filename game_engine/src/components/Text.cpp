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
Text::Text(const std::string text) : _text(text) {}

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
std::string Text::getText() const {
    return this->_text;
}

/**
 * @brief Set the text of the Text component.
 *
 * This function sets a new text value for the component.
 *
 * @param text The new text to be set.
 */
void Text::setText(std::string text) {
    this->_text = text;
}

/**
 * @brief Display the Text component information.
 *
 * This function displays a message indicating that the text component is being displayed.
 */
void Text::display() const {
    std::cout << "Text component displayed!" << std::endl;
}