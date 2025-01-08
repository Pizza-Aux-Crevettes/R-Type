/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.cpp
*/

#include "component/map/MapManager.hpp"
#include "util/Logger.hpp"

namespace fs = std::filesystem;

MapManager& MapManager::get() {
    static MapManager instance;
    return instance;
}

void MapManager::preloadMapsFromFolder(const std::string& folderPath) {
    Logger::info("[MapManager] Starting to preload maps from folder: " +
                 folderPath);

    int mapId = 1;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".map") {
            try {
                auto map = loadMapFromFile(entry.path().string());
                _maps[mapId++] = map;

                Logger::info("[MapManager] Successfully loaded map: " +
                             entry.path().string());
            } catch (const std::exception& e) {
                Logger::error("[MapManager] Failed to load map: " +
                              entry.path().string() + ". Error: " + e.what());
            }
        }
    }

    Logger::info("[MapManager] Preloaded " + std::to_string(_maps.size()) +
                 " maps.");
}

std::shared_ptr<Map> MapManager::loadMapFromFile(const std::string& filePath) {
    Logger::info("[MapManager] Loading map from file: " + filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open map file: " + filePath);
    }

    std::string name;
    std::vector<Obstacle> obstacles;
    std::string line;
    bool parsingMap = false;
    int y = 0;

    while (std::getline(file, line)) {
        if (line.find("name=") == 0) {
            name = line.substr(5);

            Logger::info("[MapManager] Map name set to: " + name);
        } else if (line == "map=###") {
            parsingMap = true;

            Logger::info("[MapManager] Starting to parse map layout.");
            continue;
        } else if (parsingMap && line != "###") {
            for (size_t x = 0; x < line.size(); x += 4) {
                std::string block = line.substr(x, 4);

                if (block == "0001") {
                    obstacles.emplace_back(ObstacleType::BLOCK,
                                           static_cast<int>(x / 4), y);
                }
            }

            y++;
        }
    }

    file.close();

    Logger::info("[MapManager] Finished parsing map: " + name +
                 ". Total obstacles: " + std::to_string(obstacles.size()));

    return std::make_shared<Map>(name, obstacles);
}

std::shared_ptr<Map> MapManager::getMapById(int mapId) const {
    Logger::info("[MapManager] Retrieving map with ID: " +
                 std::to_string(mapId));

    auto it = _maps.find(mapId);
    if (it != _maps.end()) {
        return it->second;
    }

    Logger::error("[MapManager] Map with ID " + std::to_string(mapId) +
                  " not found.");
    throw std::runtime_error("Map with ID " + std::to_string(mapId) +
                             " not found.");
}