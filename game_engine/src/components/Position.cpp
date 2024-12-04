/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.cpp
**
** The Position class represents a 2D position with `x` and `y` coordinates.
** It provides methods to get and set the values of `x` and `y` coordinates.
** The constructor allows initializing the position, and default values are set
*to 0.0f for both coordinates.
*/

#include "components/Position.hpp"
#include <iostream>

Position::Position(float x, float y) : _x(x), _y(y) {}

Position::~Position() {}

float Position::getPositionX() const {
    return this->_x;
}

float Position::getPositionY() const {
    return this->_y;
}

void Position::setPositionX(float x) {
    this->_x = x;
}

void Position::setPositionY(float y) {
    this->_y = y;
}

void Position::display() const {
    std::cout << "Position component displayed!" << std::endl;
}