/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.cpp
*/

#include "component/player/Player.hpp"
#include "component/attr/IDManager.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 * @param playerId The player's ID
 * @param name The player's name
 * @param position The player's position
 */
Player::Player(const std::string& name, const Point& position, int16_t health)
    : _id(IDManager::getNextId()), _name(name), _position(position),
      _health(health), _clientSocket(std::nullopt) {}

/**
 * @brief Get the player's ID
 *
 * @return The player's ID
 */
int32_t Player::getId() const {
    return _id;
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
 * @brief Get the client socket associated with the player
 *
 * @return std::optional<int>
 */
std::optional<int> Player::getClientSocket() const {
    return _clientSocket;
}

/**
 * @brief Associate a client socket with the player
 *
 * @param clientSocket The client socket ID
 */
void Player::setClientSocket(int clientSocket) {
    _clientSocket = clientSocket;
}

/**
 * @brief Take damage
 *
 * @param damage The amount of damage to take
 */
void Player::takeDamage(int16_t damage) {
    _health -= damage;
    if (_health <= 0) {
        Logger::info("[Player] Player " + _name + " died.");
    }
}

/**
 * @brief Get the player's health
 *
 * @return int16_t The player's health
 */
int16_t Player::getHealth() const {
    return _health;
}

/**
 * @brief Set the player's health
 *
 * @param health The new health
 */
void Player::setHealth(int16_t health) {
    _health = health;
}

/**
 * @brief Get the player's max health
 *
 * @return int16_t The player's max health
 */
int16_t Player::getMaxHealth() const {
    return DEFAULT_HEALTH;
}
