/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.cpp
*/

#include "Bullet.hpp"

Point Bullet::getSize() const {
    return size;
}

void Bullet::setSize(const Point& newSize) {
    size = newSize;
}

Point Bullet::getPosition() const {
    return position;
}

void Bullet::setPosition(const Point& pos) {
    position = pos;
}

std::vector<double> Bullet::getMoveVector() const {
    return moveVector;
}

void Bullet::setMoveVector(const std::vector<double>& vector) {
    moveVector = vector;
}

BulletType Bullet::getType() const {
    return type;
}

void Bullet::setType(BulletType newType) {
    type = newType;
}
