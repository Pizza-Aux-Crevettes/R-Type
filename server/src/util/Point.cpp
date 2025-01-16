/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.cpp
*/

#include "util/Point.hpp"

/**
 * @brief Construct a new Point:: Point object
 *
 * @param x The x position
 * @param y The y position
 */
Point::Point(const double x, const double y) : _x(x), _y(y) {}

/**
 * @brief Get the x position
 *
 * @return double The x position
 */
double Point::getX() const {
    return _x;
}

/**
 * @brief Set the x position
 *
 * @param x The x position
 */
void Point::setX(const double x) {
    _x = x;
}

/**
 * @brief Get the y position
 *
 * @return double The y position
 */
double Point::getY() const {
    return _y;
}

/**
 * @brief Set the y position
 *
 * @param y The y position
 */
void Point::setY(const double y) {
    _y = y;
}

/**
 * @brief Get the point
 *
 * @return Point
 */
Point Point::getPoint() const {
    return Point(_x, _y);
}

/**
 * @brief Set the point
 *
 * @param x The x position
 * @param y The y position
 */
void Point::setPoint(const double x, const double y) {
    _x = x;
    _y = y;
}

/**
 * @brief Normalize the point
 *
 */
void Point::normalize() {
    double magnitude = std::sqrt(_x * _x + _y * _y);
    if (magnitude > 0) {
        _x /= magnitude;
        _y /= magnitude;
    }
}
