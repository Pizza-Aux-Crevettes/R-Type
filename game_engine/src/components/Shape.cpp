/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shape.cpp
**
** The Shape class represents the visual and geometric representation of an
*object.
** It defines properties such as dimensions, color, and texture coordinates.
** Shapes can be used to render objects on the screen and interact with other
*components,
** like physics or collision systems.
** This class provides methods to create, modify, and retrieve information about
*shapes.
*/

#include "components/Shape.hpp"
#include <iostream>

Shape::Shape(ShapeType type, std::pair<double, double> size, float radius)
    : _type(type), _size(size), _radius(radius) {}

std::pair<double, double> Shape::getSize() const {
    return _size;
}

void Shape::setSize(std::pair<double, double> size) {
    _size = size;
}

void Shape::display() const {
    std::cout << "Shape component displayed!" << std::endl;
}

ShapeType Shape::getShapeType() const {
    return _type;
}

sf::RectangleShape& Shape::getRect() {
    return _rect;
}

sf::CircleShape& Shape::getCircle() {
    return _circle;
}

bool Shape::getIsLoaded() const {
    return _isLoad;
}

void Shape::setIsLoaded(bool isLoad) {
    _isLoad = isLoad;
}

float Shape::getRadius() const {
    return _radius;
}

void Shape::setShape(const sf::RectangleShape& rect) {
    _rect = rect;
}

void Shape::setShape(const sf::CircleShape& circle) {
    _circle = circle;
}

Shape::~Shape() {}