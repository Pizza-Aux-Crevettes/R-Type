/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "component/player/Player.hpp"
#include "util/Logger.hpp"

Player::Player(const int32_t playerId, std::string name, const Point& position,
               const Point& size, const double speed)
    : _playerId(playerId), _name(std::move(name)), _position(position),
      _size(size), _speed(speed), _health(Health()),
      _threadId(std::thread::id()) {}

int32_t Player::getId() const {
    return _playerId;
}

const std::string& Player::getName() const {
    return _name;
}

const Point& Player::getPosition() const {
    return _position;
}

const Point& Player::getSize() const {
    return _size;
}

const Health& Player::getHealth() const {
    return _health;
}

double Player::getSpeed() const {
    return _speed;
}

std::thread::id Player::getThreadId() const {
    return _threadId;
}

const sockaddr_in& Player::getClientAddress() const {
    return _clientAddr;
}

void Player::setPosition(const Point& position) {
    _position = position;
}

void Player::setThreadId(const std::thread::id& threadId) {
    _threadId = threadId;
}

void Player::setClientAddress(const sockaddr_in& clientAddr) {
    _clientAddr = clientAddr;
}

void Player::move(const double deltaX, const double deltaY) {
    _position.setX(_position.getX() + deltaX);
    _position.setY(_position.getY() + deltaY);
}
