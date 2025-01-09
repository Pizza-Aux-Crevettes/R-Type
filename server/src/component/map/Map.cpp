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
