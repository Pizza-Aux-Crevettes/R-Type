/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "component/player/Player.hpp"

Player::Player(const std::string& name, const Point& position,
               const Point& size, double speed)
    : _name(name), _position(position), _size(size), _speed(speed),
      _health(Health()) {}

const std::string& Player::getName() const {
    return _name;
}

const Point& Player::getPosition() const {
    return _position;
}

const Point& Player::getSize() const {
    return _size;
}

double Player::getSpeed() const {
    return _speed;
}

const Health& Player::getHealth() const {
    return _health;
}

void Player::move(double deltaX, double deltaY) {
    _position.setX(_position.getX() + deltaX);
    _position.setY(_position.getY() + deltaY);
}

void Player::setPosition(const Point& position) {
    _position = position;
}
