/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.cpp
*/

#include "util/Point.hpp"
#include "util/Logger.hpp"

Point::Point(double x, double y) : _x(x), _y(y) {}

double Point::getX() const {
    return _x;
}

double Point::getY() const {
    return _y;
}

void Point::setX(double x) {
    _x = x;
}

void Point::setY(double y) {
    _y = y;
}
