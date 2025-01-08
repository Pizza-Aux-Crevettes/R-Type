/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.cpp
*/

#include "util/Point.hpp"

Point::Point(const double x, const double y) : _x(x), _y(y) {}

double Point::getX() const {
    return _x;
}

double Point::getY() const {
    return _y;
}

Point Point::getPoint() const {
    return Point(_x, _y);
}

void Point::setX(const double x) {
    _x = x;
}

void Point::setY(const double y) {
    _y = y;
}

void Point::setPoint(const double x, const double y) {
    _x = x;
    _y = y;
}
