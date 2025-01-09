/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.cpp
*/

#include "component/map/MapManager.hpp"
#include "util/Logger.hpp"

namespace fs = std::filesystem;

/**
 * @brief Get the MapManager instance
 *
 * @return MapManager&
 */
MapManager& MapManager::get() {
    static MapManager instance;
    return instance;
}

/**
 * @brief Preload all maps from a folder
 *
 * @param folderPath The path to the folder containing the maps
 */
void MapManager::preloadMapsFromFolder(const std::string& folderPath) {
    Logger::info("[MapManager] Preloading maps from folder: " + folderPath);

    int mapId = 1;
    int loadedCount = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".map") {
            try {
                auto map = loadMapFromFile(entry.path().string());

                _maps[mapId++] = map;
                loadedCount++;
            } catch (const std::exception& e) {
                Logger::error("[MapManager] Failed to load map: " +
                              entry.path().filename().string() +
                              ". Error: " + e.what());
            }
        }
    }

    Logger::success("[MapManager] Preloaded " + std::to_string(loadedCount) +
                    " map(s).");
}

/**
 * @brief Load a map from a file
 *
 * @param filePath The path to the map file
 * @return std::shared_ptr<Map> The loaded map
 */
std::shared_ptr<Map> MapManager::loadMapFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::error("[MapManager] Unable to open map file: " +
                      fs::path(filePath).filename().string());
        throw std::runtime_error("Failed to open map file: " + filePath);
    }

    std::string name;
    std::vector<Obstacle> obstacles;
    std::string line;
    bool parsingMap = false;
    int y = 0;

    while (std::getline(file, line)) {
        if (line.find(NAME_LABEL) == 0) {
            name = line.substr(NAME_OFFSET);
        } else if (line == MAP_LABEL) {
            parsingMap = true;
            continue;
        } else if (parsingMap) {
            if (line == END_LABEL) {
                parsingMap = false;
                continue;
            }

            parseMapLine(line, y++, obstacles);
        }
    }

    file.close();

    if (name.empty()) {
        Logger::error("[MapManager] Missing map name in file: " +
                      fs::path(filePath).filename().string());
        throw std::runtime_error("Map file is missing a name: " + filePath);
    }

    Logger::success("[MapManager] Successfully loaded map: " + name + " with " +
                    std::to_string(obstacles.size()) + " obstacles.");

    return std::make_shared<Map>(name, obstacles);
}

/**
 * @brief Parse a line of the map file
 *
 * @param line The line to parse
 * @param y The y position of the line
 * @param obstacles The vector to store the obstacles
 */
void MapManager::parseMapLine(const std::string& line, int y,
                              std::vector<Obstacle>& obstacles) {
    for (size_t x = 0; x < line.size(); x += BLOCK_OFFSET) {
        std::string blockCode = line.substr(x, BLOCK_OFFSET);

        if (_obstacleMapping.find(blockCode) != _obstacleMapping.end()) {
            obstacles.emplace_back(_obstacleMapping.at(blockCode),
                                   static_cast<int>(x / BLOCK_OFFSET), y);
        }
    }
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

    Logger::error("[MapManager] Map with ID " + std::to_string(mapId) +
                  " not found.");
    throw std::runtime_error("Map with ID " + std::to_string(mapId) +
                             " not found.");
}
