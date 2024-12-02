/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.cpp
**
** The Button class represents a UI button with a text label and a size.
** It holds a `text` as a string and `size` as a `sf::Vector2f` for the button's
*width and height.
** The constructor allows initializing these attributes with default values.
*/

#include "components/Button.hpp"

Button::Button(std::string text, sf::Vector2f size)
    : _text(text), _size(size) {}

Button::~Button() {}

std::string Button::getText() const {
    return this->_text;
}

void Button::setText(std::string text) {
    this->_text = text;
}

sf::Vector2f Button::getSize() const {
    return this->_size;
}

void Button::setSize(sf::Vector2f size) {
    this->_size = size;
}
