/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Enemy.cpp
*/

#include "Enemy.hpp"

int Enemy::getId() const {
    return id;
}

void Enemy::setId(int newId) {
    id = newId;
}

Point Enemy::getPosition() const {
    return position;
}

void Enemy::setPosition(const Point& pos) {
    position = pos;
}

Point Enemy::getSize() const {
    return size;
}

void Enemy::setSize(const Point& newSize) {
    size = newSize;
}

std::vector<double> Enemy::getMoveVector() const {
    return moveVector;
}

void Enemy::setMoveVector(const std::vector<double>& vector) {
    moveVector = vector;
}

Health Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(const Health& newHealth) {
    health = newHealth;
}
