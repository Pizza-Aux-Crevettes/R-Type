/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "component/player/Player.hpp"
#include "component/attr/IDManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 * @param playerId The player's ID
 * @param name The player's name
 * @param position The player's position
 * @param size The player's size
 * @param speed The player's speed
 */
Player::Player(const std::string& name, const Point& position,
               const Point& size, double speed)
    : _id(IDManager::getNextId()), _name(name), _position(position),
      _size(size), _speed(speed), _health(Health()),
      _threadId(std::thread::id()) {}

/**
 * @brief Get the player's ID
 *
 * @return The player's ID
 */
int32_t Player::getId() const {
    return _playerId;
}

/**
 * @brief Get the player's name
 *
 * @return The player's name
 */
const std::string& Player::getName() const {
    return _name;
}

/**
 * @brief Get the player's position
 *
 * @return The player's position
 */
const Point& Player::getPosition() const {
    return _position;
}

/**
 * @brief Set the player's position
 *
 * @param position The new position
 */
void Player::setPosition(const Point& position) {
    _position = position;
}

/**
 * @brief Set the player's thread ID
 *
 * @param threadId The thread ID
 */
const Point& Player::getSize() const {
    return _size;
}

/**
 * @brief Set the player's thread ID
 *
 * @param threadId The thread ID
 */
const Health& Player::getHealth() const {
    return _health;
}

/**
 * @brief Set the player's thread ID
 *
 * @param threadId The thread ID
 */
double Player::getSpeed() const {
    return _speed;
}

/**
 * @brief Move the player
 *
 * @param deltaX The delta X
 * @param deltaY The delta Y
 */
void Player::move(const double deltaX, const double deltaY) {
    _position.setX(_position.getX() + deltaX);
    _position.setY(_position.getY() + deltaY);
}
