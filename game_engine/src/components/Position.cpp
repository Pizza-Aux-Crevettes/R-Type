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

/**
 * @brief Constructor for the Position component.
 *
 * This constructor initializes the Position component with the given x and y
 * coordinates.
 *
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
Position::Position(std::pair<float, float> pos)
    : _x(pos.first), _y(pos.second) {}

/**
 * @brief Destructor for the Position component.
 *
 * This destructor cleans up any resources used by the Position component.
 */
Position::~Position() {}

/**
 * @brief Get the x-coordinate of the Position component.
 *
 * This function retrieves the x-coordinate of the Position component.
 *
 * @return The x-coordinate of the position.
 */
float Position::getPositionX() const {
    return this->_x;
}

/**
 * @brief Get the y-coordinate of the Position component.
 *
 * This function retrieves the y-coordinate of the Position component.
 *
 * @return The y-coordinate of the position.
 */
float Position::getPositionY() const {
    return this->_y;
}

/**
 * @brief Set the x-coordinate of the Position component.
 *
 * This function sets the x-coordinate of the Position component.
 *
 * @param x The new x-coordinate for the position.
 */
void Position::setPositionX(float x) {
    this->_x = x;
}

/**
 * @brief Set the y-coordinate of the Position component.
 *
 * This function sets the y-coordinate of the Position component.
 *
 * @param y The new y-coordinate for the position.
 */
void Position::setPositionY(float y) {
    this->_y = y;
}

/**
 * @brief Display the Position component information.
 *
 * This function displays a message indicating that the Position component is
 * being displayed.
 */
void Position::display() const {
    std::cout << "Position component displayed!" << std::endl;
}