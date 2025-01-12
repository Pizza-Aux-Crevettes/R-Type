/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.cpp
*/

#include "component/map/MapManager.hpp"
#include "component/map/MapFileLoader.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new MapManager:: Map Manager object
 *
 */
MapManager& MapManager::get() {
    static MapManager instance;
    return instance;
}

/**
 * @brief Preload maps from a folder
 *
 * @param folderPath The path to the folder containing the maps
 */
void MapManager::preloadMapsFromFolder(const std::string& folderPath) {
    Logger::info("[MapManager] Preloading maps from folder: " + folderPath);

    MapFileLoader fileLoader;
    auto maps = fileLoader.loadMapsFromFolder(folderPath);

    int mapId = 1;
    for (const auto& map : maps) {
        _maps[mapId++] = map;
    }

    Logger::success("[MapManager] Preloaded " + std::to_string(_maps.size()) +
                    " map(s).");
}

/**
 * @brief Get a map by its ID
 *
 * @param mapId The ID of the map
 * @return std::shared_ptr<Map> The map
 */
std::shared_ptr<Map> MapManager::getMapById(int mapId) const {
    auto it = _maps.find(mapId);
    if (it != _maps.end()) {
        return it->second;
    }
    throw std::runtime_error("Map with ID " + std::to_string(mapId) +
                             " not found.");
}

/**
 * @brief Set the current map
 *
 * @param mapId The ID of the map
 */
void MapManager::setCurrentMap(int mapId) {
    auto map = getMapById(mapId);
    _currentMap = map;

    Logger::success("[MapManager] Current map set to ID: " +
                    std::to_string(mapId));
}

/**
 * @brief Get the current map
 *
 * @return std::shared_ptr<Map> The current map
 */
std::shared_ptr<Map> MapManager::getCurrentMap() const {
    if (!_currentMap) {
        throw std::runtime_error("No current map is set.");
    }
    return _currentMap;
}
