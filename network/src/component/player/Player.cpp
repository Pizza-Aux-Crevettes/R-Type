/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

/**
 * @file Player.cpp
 * @brief Represents a player in the game, with attributes such as position,
 * size, speed, health, and thread association.
 */

#include "component/player/Player.hpp"
#include "util/Logger.hpp"

/**
 * @brief Constructs a new Player.
 *
 * @param playerId The unique ID of the player.
 * @param name The name of the player.
 * @param position The initial position of the player.
 * @param size The size of the player (e.g., width and height).
 * @param speed The movement speed of the player.
 */
Player::Player(int32_t playerId, const std::string& name, const Point& position,
               const Point& size, double speed)
    : _userId(playerId), _name(name), _position(position), _size(size),
      _speed(speed), _health(Health()), _threadId(std::thread::id()) {
    Logger::info("[Player] Created player: " + std::to_string(playerId) +
                 " at position (" + std::to_string(position.getX()) + ", " +
                 std::to_string(position.getY()) + ")");
}

/**
 * @brief Updates the player's position.
 *
 * @param position The new position of the player.
 */
void Player::setPosition(const Point& position) {
    Logger::info(
        "[Player] Setting position for player: " + std::to_string(_userId) +
        " to (" + std::to_string(position.getX()) + ", " +
        std::to_string(position.getY()) + ")");

    _position = position;
}

/**
 * @brief Retrieves the current position of the player.
 *
 * @return A constant reference to the player's position.
 */
const Point& Player::getPosition() const {
    return _position;
}

/**
 * @brief Retrieves the thread ID associated with the player.
 *
 * @return The thread ID.
 */
std::thread::id Player::getThreadId() const {
    return _threadId;
}

/**
 * @brief Associates the player with a specific thread ID.
 *
 * @param threadId The thread ID to associate with the player.
 */
void Player::setThreadId(const std::thread::id& threadId) {
    _threadId = threadId;
}

/**
 * @brief Retrieves the player's unique ID.
 *
 * @return The player's ID.
 */
int32_t Player::getId() const {
    return _userId;
}

/**
 * @brief Retrieves the player's name.
 *
 * @return The player's name.
 */
const std::string& Player::getName() const {
    return _name;
}

/**
 * @brief Retrieves the size of the player.
 *
 * @return A constant reference to the player's size.
 */
const Point& Player::getSize() const {
    return _size;
}

/**
 * @brief Retrieves the player's speed.
 *
 * @return The player's speed.
 */
double Player::getSpeed() const {
    return _speed;
}

/**
 * @brief Retrieves the player's health attributes.
 *
 * @return A constant reference to the player's health.
 */
const Health& Player::getHealth() const {
    return _health;
}

/**
 * @brief Moves the player by a specified delta in the X and Y directions.
 *
 * @param deltaX The change in the X position.
 * @param deltaY The change in the Y position.
 */
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
