/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.cpp
*/

#include "Obstacle.hpp"

Point Obstacle::getPosition() const {
    return position;
}

void Obstacle::setPosition(const Point& pos) {
    position = pos;
}

ObstacleType Obstacle::getType() const {
    return type;
}

void Obstacle::setType(ObstacleType newType) {
    type = newType;
}

Point Obstacle::getSize() const {
    return size;
}

void Obstacle::setSize(const Point& newSize) {
    size = newSize;
}
