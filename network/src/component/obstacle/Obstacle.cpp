/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.cpp
*/

#include "component/obstacle/Obstacle.hpp"

Obstacle::Obstacle()
    : _type(ObstacleType::NONE), _width(0), _height(0), _x(0), _y(0),
      _traversable(true) {}

Obstacle::Obstacle(ObstacleType type, int width, int height, int x, int y,
                   bool traversable)
    : _type(type), _width(width), _height(height), _x(x), _y(y),
      _traversable(traversable) {}

ObstacleType Obstacle::getType() const {
    return _type;
}

std::pair<int, int> Obstacle::getSize() const {
    return {_width, _height};
}

std::pair<int, int> Obstacle::getPosition() const {
    return {_x, _y};
}

bool Obstacle::isTraversable() const {
    return _traversable;
}
