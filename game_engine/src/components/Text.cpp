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

Text::Text(const std::string text) : _text(text) {}

Text::~Text() {}

std::string Text::getText() const {
    return this->_text;
}

void Text::setText(std::string text) {
    this->_text = text;
}

void Text::display() const {
    std::cout << "Text component displayed!" << std::endl;
}