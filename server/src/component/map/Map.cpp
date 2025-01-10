/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.cpp
*/

#include "component/map/Map.hpp"

/**
 * @brief Construct a new Map:: Map object
 *
 * @param name The name of the map
 * @param obstacles The obstacles of the map
 */
Map::Map(const std::string& name,
         const std::vector<std::shared_ptr<Obstacle>>& obstacles)
    : _name(name), _obstacles(obstacles), _viewport(0) {}

/**
 * @brief Increment the viewport of the map
 */
void Map::incrementViewport() {
    _viewport += 1;
}

/**
 * @brief Get the viewport of the map
 *
 * @return int32_t
 */
int32_t Map::getViewport() const {
    return _viewport;
}

/**
 * @brief Get the obstacles of the map by viewport
 *
 * @param authorizedBlock The number of blocks authorized
 * @return std::vector<Obstacle>
 */
std::vector<std::shared_ptr<Obstacle>> Map::getObstaclesByViewport() const {
    int32_t startX = _viewport;
    int32_t endX = _viewport + RENDER_DISTANCE;

    std::vector<std::shared_ptr<Obstacle>> visibleObstacles;

    for (const auto& obstacle : _obstacles) {
        if (obstacle->getPosition().getX() >= startX &&
            obstacle->getPosition().getX() <= endX) {
            visibleObstacles.push_back(obstacle);
        }
    }

    return visibleObstacles;
}

/**
 * @brief Check if a block is void
 *
 * @param x The x position of the block
 * @param y The y position of the block
 * @return bool
 */
bool Map::isVoidBlock(int32_t x, int32_t y) const {
    for (const auto& obstacle : _obstacles) {
        if (obstacle->getPosition().getX() == x &&
            obstacle->getPosition().getY() == y) {
            return obstacle->getType() == ObstacleType::NONE;
        }
    }
    return true;
}
