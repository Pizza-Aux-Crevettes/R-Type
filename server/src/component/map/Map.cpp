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
Map::Map(const std::string& name, const std::vector<Obstacle>& obstacles)
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
 * @return int
 */
int Map::getViewport() const {
    return _viewport;
}

/**
 * @brief Get the obstacles of the map
 *
 * @return const std::vector<Obstacle>&
 */
const std::vector<Obstacle>& Map::getObstacles() const {
    return _obstacles;
}

/**
 * @brief Get the obstacles of the map by viewport
 *
 * @param authorizedBlock The number of blocks authorized
 * @return std::vector<Obstacle>
 */
std::vector<Obstacle> Map::getObstaclesByViewport() const {
    int startX = _viewport;
    int endX = _viewport + RENDER_DISTANCE;

    std::vector<Obstacle> visibleObstacles;

    for (const auto& obstacle : _obstacles) {
        if (obstacle._x >= startX && obstacle._x <= endX) {
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
bool Map::isVoidBlock(int x, int y) const {
    for (const auto& obstacle : _obstacles) {
        if (obstacle._x == x && obstacle._y == y) {
            return obstacle._type == ObstacleType::NONE;
        }
    }
    return true;
}
