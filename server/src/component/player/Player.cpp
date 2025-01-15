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
Player::Player(const std::string& name, const Point& position)
    : _id(IDManager::getNextId()), _name(name), _position(position), _clientSocket(std::nullopt) {}

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
