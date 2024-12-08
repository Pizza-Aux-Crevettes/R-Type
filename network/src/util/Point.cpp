/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.cpp
*/

#include "util/Point.hpp"
#include "util/Logger.hpp"

Point::Point(double x, double y) : _x(x), _y(y) {
    Logger::info("[Point] Created Point at (" + std::to_string(x) + ", " +
                 std::to_string(y) + ")");
}

double Point::getX() const {
    Logger::debug("[Point] Accessed X: " + std::to_string(_x));

    return _x;
}

double Point::getY() const {
    Logger::debug("[Point] Accessed Y: " + std::to_string(_y));

    return _y;
}

void Point::setX(double x) {
    Logger::info("[Point] Updated X from " + std::to_string(_x) + " to " +
                 std::to_string(x));

    _x = x;
}

void Point::setY(double y) {
    Logger::info("[Point] Updated Y from " + std::to_string(_y) + " to " +
                 std::to_string(y));

    _y = y;
}
