/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.cpp
**
** The Button class represents a UI button with a text label and a size.
** It holds a `text` as a string and `size` as a `std::pair<double, double>` for
*the button's
** width and height.
** The constructor allows initializing these attributes with default values.
*/

#include "components/Button.hpp"
#include <iostream>

/**
 * @brief Constructor for the Button component.
 *
 * This constructor initializes the Button component with the specified text and size.
 *
 * @param text A string representing the text on the button.
 * @param size A pair of doubles representing the size of the button (width, height).
 */
Button::Button(std::string text, std::pair<double, double> size)
    : _text(text), _size(size) {}

/**
 * @brief Destructor for the Button component.
 *
 * This destructor cleans up any resources used by the Button component.
 */
Button::~Button() {}

/**
 * @brief Get the text of the Button component.
 *
 * This function retrieves the text displayed on the button.
 *
 * @return A string representing the text on the button.
 */
std::string Button::getText() const {
    return this->_text;
}

/**
 * @brief Set the text of the Button component.
 *
 * This function sets the text displayed on the button.
 *
 * @param text A string representing the new text to display on the button.
 */
void Button::setText(std::string text) {
    this->_text = text;
}

/**
 * @brief Get the size of the Button component.
 *
 * This function retrieves the size of the button as a pair of doubles.
 *
 * @return A pair of doubles representing the size of the button (width, height).
 */
std::pair<double, double> Button::getSize() const {
    return this->_size;
}

/**
 * @brief Set the size of the Button component.
 *
 * This function sets the size of the button as a pair of doubles.
 *
 * @param size A pair of doubles representing the new size of the button (width, height).
 */
void Button::setSize(std::pair<double, double> size) {
    this->_size = size;
}

/**
 * @brief Display the Button component information.
 *
 * This function displays a message indicating that the Button component is being displayed.
 */
void Button::display() const {
    std::cout << "Button component displayed!" << std::endl;
}