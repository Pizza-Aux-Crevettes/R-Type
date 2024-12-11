/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "component/player/Player.hpp"
#include "util/Logger.hpp"

Player::Player(int32_t playerId, const std::string& name, const Point& position,
               const Point& size, double speed)
    : _userId(playerId), _name(name), _position(position), _size(size),
      _speed(speed), _health(Health()), _threadId(std::thread::id()) {
    Logger::info("[Player] Created player: " + std::to_string(playerId) +
                 " at position (" + std::to_string(position.getX()) + ", " +
                 std::to_string(position.getY()) + ")");
}

void Player::setPosition(const Point& position) {
    Logger::info(
        "[Player] Setting position for player: " + std::to_string(_userId) +
        " to (" + std::to_string(position.getX()) + ", " +
        std::to_string(position.getY()) + ")");

    _position = position;
}

const Point& Player::getPosition() const {
    return _position;
}

std::thread::id Player::getThreadId() const {
    return _threadId;
}

void Player::setThreadId(const std::thread::id& threadId) {
    _threadId = threadId;
}

int32_t Player::getId() const {
    return _userId;
}

const std::string& Player::getName() const {
    return _name;
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
    Logger::info("[Player] Moving player: " + std::to_string(_userId) +
                 " by (" + std::to_string(deltaX) + ", " +
                 std::to_string(deltaY) + ")");

    _position.setX(_position.getX() + deltaX);
    _position.setY(_position.getY() + deltaY);

    Logger::info(
        "[Player] New position for player: " + std::to_string(_userId) +
        " - (" + std::to_string(_position.getX()) + ", " +
        std::to_string(_position.getY()) + ")");
}
