/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "Player.hpp"

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

Point Player::getPosition() const {
    return position;
}

void Player::setPosition(const Point& pos) {
    position = pos;
}

Point Player::getSize() const {
    return size;
}

void Player::setSize(const Point& newSize) {
    size = newSize;
}

double Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(double newSpeed) {
    speed = newSpeed;
}

Health Player::getHealth() const {
    return health;
}

void Player::setHealth(const Health& newHealth) {
    health = newHealth;
}

Inventory Player::getInventory() const {
    return inventory;
}

void Player::setInventory(const Inventory& newInventory) {
    inventory = newInventory;
}
