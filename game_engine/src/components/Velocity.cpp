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
#include <iostream>

/**
 * @brief Constructor for the Velocity component.
 *
 * This constructor initializes the velocity component with the given x and y
 * values.
 *
 * @param x The velocity along the X-axis.
 * @param y The velocity along the Y-axis.
 */
Velocity::Velocity(float x, float y) : _x(x), _y(y) {}

/**
 * @brief Destructor for the Velocity component.
 *
 * This destructor cleans up any resources used by the velocity component.
 */
Velocity::~Velocity() {}

/**
 * @brief Get the velocity along the X-axis.
 *
 * This function retrieves the velocity value along the X-axis.
 *
 * @return The velocity along the X-axis.
 */
float Velocity::getVelocityX() const {
    return this->_x;
}

/**
 * @brief Set the velocity along the X-axis.
 *
 * This function sets the velocity value along the X-axis.
 *
 * @param x The new velocity value to set for the X-axis.
 */
void Velocity::setVelocityX(float x) {
    this->_x = x;
}

/**
 * @brief Get the velocity along the Y-axis.
 *
 * This function retrieves the velocity value along the Y-axis.
 *
 * @return The velocity along the Y-axis.
 */
float Velocity::getVelocityY() const {
    return this->_y;
}

/**
 * @brief Set the velocity along the Y-axis.
 *
 * This function sets the velocity value along the Y-axis.
 *
 * @param y The new velocity value to set for the Y-axis.
 */
void Velocity::setVelocityY(float y) {
    this->_y = y;
}

/**
 * @brief Display the Velocity component information.
 *
 * This function displays a message indicating that the velocity component is
 * being displayed.
 */
void Velocity::display() const {
    std::cout << "Velocity component displayed!" << std::endl;
}