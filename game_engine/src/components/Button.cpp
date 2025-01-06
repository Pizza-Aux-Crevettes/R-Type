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
 * This constructor initializes the Button component with the specified text and
 * size.
 *
 * @param text A string representing the text on the button.
 * @param size A pair of doubles representing the size of the button (width,
 * height).
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
 * @return A pair of doubles representing the size of the button (width,
 * height).
 */
std::pair<double, double> Button::getSize() const {
    return this->_size;
}

/**
 * @brief Set the size of the Button component.
 *
 * This function sets the size of the button as a pair of doubles.
 *
 * @param size A pair of doubles representing the new size of the button (width,
 * height).
 */
void Button::setSize(std::pair<double, double> size) {
    this->_size = size;
}

/**
 * @brief Get the shape of the Button component.
 *
 * This function gets the sf::RectangleShape of the button.
 *
 * @return An sf::RectangleShape object representing the button.
 */
sf::RectangleShape& Button::getShape() {
    return this->_button;
}

/**
 * @brief Set the shape of the Button component.
 *
 * This function sets the sf::RectangleShape of the button.
 *
 * @param shape An sf::RectangleShape object representing the button.
 */
void Button::setShape(const sf::RectangleShape& shape) {
    this->_button = shape;
}

/**
 * @brief Get whether the Button component is loaded.
 *
 * This function checks if the Button component has been initialized.
 *
 * @return True if the Button is loaded, false otherwise.
 */
bool Button::getIsLoaded() const {
    return this->_isLoad;
}

/**
 * @brief Set whether the Button component is loaded.
 *
 * This function sets the loaded state of the Button component.
 */
void Button::setIsLoaded() {
    this->_isLoad = !this->_isLoad;
}

/**
 * @brief Get whether the Button component is checked.
 *
 * This function checks if the Button component has been activated.
 *
 * @return True if the Button is active, false otherwise.
 */
bool Button::getChecked() const {
    return this->_isChecked;}

/**
 * @brief Set whether the Button component is checked.
 *
 * This function sets the activated state of the Button component.
 */
void Button::setChecked() {
    this->_isChecked = !this->_isChecked;
}

/**
 * @brief Set function for callback.
 *
 * This function sets the callback state of the Slider component.
 * @param callback An std::function object representing the function to callback.
 */
void Button::setCallback(std::function<void()> callback) {
    _callback = callback;
}

/**
 * @brief Execute function callback.
 *
 * This function call the function in callback of the Slider component.
 */
void Button::executeCallback() {
    if (_callback) {
        _callback();
    }
}

/**
 * @brief Display the Button component information.
 *
 * This function displays a message indicating that the Button component is
 * being displayed.
 */
void Button::display() const {
    std::cout << "Button component displayed!" << std::endl;
}