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

Button::Button(std::string text, std::pair<double, double> size)
    : _text(text), _size(size) {}

Button::~Button() {}

std::string Button::getText() const {
    return this->_text;
}

void Button::setText(std::string text) {
    this->_text = text;
}

std::pair<double, double> Button::getSize() const {
    return this->_size;
}

void Button::setSize(std::pair<double, double> size) {
    this->_size = size;
}
