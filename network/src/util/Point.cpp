/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.cpp
*/

/**
 * @file Point.cpp
 * @brief Implements the Point class for 2D coordinate manipulation.
 *
 * This class provides methods for accessing and modifying 2D coordinates (x,
 * y).
 */

#include "util/Point.hpp"

/**
 * @brief Constructs a Point object with specified x and y coordinates.
 *
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 */
Point::Point(double x, double y) : _x(x), _y(y) {}

/**
 * @brief Retrieves the x-coordinate of the point.
 *
 * @return double The x-coordinate of the point.
 */
double Point::getX() const {
    return _x;
}

/**
 * @brief Retrieves the y-coordinate of the point.
 *
 * @return double The y-coordinate of the point.
 */
double Point::getY() const {
    return _y;
}

/**
 * @brief Sets the x-coordinate of the point.
 *
 * @param x The new x-coordinate to assign.
 */
void Point::setX(double x) {
    _x = x;
}

/**
 * @brief Sets the y-coordinate of the point.
 *
 * @param y The new y-coordinate to assign.
 */
void Point::setY(double y) {
    _y = y;
}
