/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.cpp
*/

#include "component/map/MapManager.hpp"

MapManager& MapManager::get() {
    static MapManager instance;

    return instance;
}

std::shared_ptr<Map> MapManager::loadMap(int mapId) {
    switch (mapId) {
    case 1:
        return std::make_shared<Map>("Map1", 100, 50, 200);
    case 2:
        return std::make_shared<Map>("Map2", 200, 100,200);
    default:
        return std::make_shared<Map>("DefaultMap", 50, 25, 200);
    }
}
