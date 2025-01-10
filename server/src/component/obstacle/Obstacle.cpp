/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.cpp
*/

#include "component/obstacle/Obstacle.hpp"
#include "component/attr/IDManager.hpp"

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
 * @return int The ID of the obstacle
 */
int Obstacle::getId() const {
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
