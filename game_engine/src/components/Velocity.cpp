/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity.cpp
**
** The Velocity class represents the velocity of an entity in the game.
** It holds two float values `x` and `y` that represent the velocity along the X
*and Y axes.
** The constructor allows initializing these values with default values.
*/

#include "components/Velocity.hpp"

Velocity::Velocity(float x, float y) : _x(x), _y(y) {}

Velocity::~Velocity() {}

float Velocity::getVelocityX() const {
    return this->_x;
}

void Velocity::setVelocityX(float x) {
    this->_x = x;
}

float Velocity::getVelocityY() const {
    return this->_y;
}

void Velocity::setVelocityY(float y) {
    this->_y = y;
}
