/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.cpp
*/

#include "component/obstacle/Obstacle.hpp"
#include "component/attr/IDManager.hpp"
#include "util/Config.hpp"

/**
 * @brief Construct a new Obstacle:: Obstacle object
 *
 * @param type The type of the obstacle
 * @param position The position of the obstacle
 */
Obstacle::Obstacle(ObstacleType type, const Point& position)
    : _id(IDManager::getNextId()), _type(type), _position(position) {}

/**
 * @brief Get the ID of the obstacle
 *
 * @return int32_t The ID of the obstacle
 */
int32_t Obstacle::getId() const {
    return _id;
}

/**
 * @brief Get the type of the obstacle
 *
 * @return ObstacleType The type of the obstacle
 */
ObstacleType Obstacle::getType() const {
    return _type;
}

/**
 * @brief Set the type of the obstacle
 *
 * @param type The new type
 */
void Obstacle::setType(ObstacleType type) {
    _type = type;
}

/**
 * @brief Get the position of the obstacle
 *
 * @return const Point& The position of the obstacle
 */
const Point& Obstacle::getPosition() const {
    return _position;
}

/**
 * @brief Set the position of the obstacle
 *
 * @param position The new position
 */
void Obstacle::setPosition(const Point& position) {
    _position = position;
}

/**
 * @brief Check if the obstacle contains a point
 *
 * @param x The x coordinate
 * @param y The y coordinate
 * @return true If the point is within the obstacle bounds
 * @return false Otherwise
 */
bool Obstacle::contains(int32_t x, int32_t y) const {
    return x >= _position.getX() && x < _position.getX() + BLOCK_SIZE &&
           y >= _position.getY() && y < _position.getY() + BLOCK_SIZE;
}

/**
 * @brief Check if the obstacle collides with a player
 *
 * @param player The player to check
 * @return true If the obstacle collides with the player
 * @return false Otherwise
 */
bool Obstacle::collidesWith(const std::shared_ptr<Player>& player) const {
    int32_t playerX = player->getPosition().getX();
    int32_t playerY = player->getPosition().getY();

    return contains(playerX, playerY) ||
           contains(playerX + PLAYER_WIDTH, playerY) ||
           contains(playerX, playerY + PLAYER_HEIGHT) ||
           contains(playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT);
}
