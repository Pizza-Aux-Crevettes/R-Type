/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.cpp
*/

#include "component/map/MapManager.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "util/Logger.hpp"

namespace fs = std::filesystem;

MapManager& MapManager::get() {
    static MapManager instance;

    return instance;
}

void MapManager::preloadMapsFromFolder(const std::string& folderPath) {
    int mapId = 1;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".map") {
            try {
                auto map = loadMapFromFile(entry.path().string());

                _maps[mapId++] = map;

                Logger::info("[MapManager] Loaded map: " +
                             entry.path().string());
            } catch (const std::exception& e) {
                Logger::error("[MapManager] Failed to load map: " +
                              std::string(e.what()));
            }
        }
    }

    Logger::info("[MapManager] Preloaded " + std::to_string(_maps.size()) +
                 " maps.");
}

std::shared_ptr<Map> MapManager::loadMapFromFile(const std::string& filePath) {
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
        } else if (line == "map=###") {
            parsingMap = true;

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

    return std::make_shared<Map>(name, obstacles);
}

std::shared_ptr<Map> MapManager::getMapById(int mapId) const {
    if (_maps.find(mapId) != _maps.end()) {
        return _maps.at(mapId);
    }

    throw std::runtime_error("Map with ID " + std::to_string(mapId) +
                             " not found.");
}
