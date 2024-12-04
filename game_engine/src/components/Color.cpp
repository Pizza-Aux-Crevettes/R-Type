/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Color.cpp
**
** The Color class represents a color for an entity in the game.
** It holds the color as a vector of doubles representing RGB values.
** The constructor allows initializing the color with a given vector of values
*(e.g., RGB).
*/

#include "components/Color.hpp"
#include <iostream>

Color::Color(std::vector<double> color) : _color(color) {}

Color::~Color() {}

std::vector<double> Color::getColor() const {
    return this->_color;
}

void Color::setColor(std::vector<double> color) {
    this->_color = color;
}

void Color::display() const {
    std::cout << "Color component displayed!" << std::endl;
}