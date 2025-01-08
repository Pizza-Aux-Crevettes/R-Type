/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.cpp
*/

#include "component/map/Map.hpp"

Map::Map(const std::string& name, const std::vector<Obstacle>& obstacles)
    : _name(name), _obstacles(obstacles), _viewport(0) {}

void Map::incrementViewport() {
    _viewport += 1;
}

int Map::getViewport() const {
    return _viewport;
}

const std::vector<Obstacle>& Map::getObstacles() const {
    return _obstacles;
}
