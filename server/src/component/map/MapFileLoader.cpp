/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapFileLoader.cpp
*/

#include "component/map/MapFileLoader.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "util/Config.hpp"
#include "util/FileReader.hpp"
#include "util/Logger.hpp"

namespace fs = std::filesystem;

/**
 * @brief Load all maps from a folder
 *
 * @param folderPath The path to the folder containing the maps
 * @return std::vector<std::shared_ptr<Map>> The loaded maps
 */
std::vector<std::shared_ptr<Map>>
MapFileLoader::loadMapsFromFolder(const std::string& folderPath) {
    std::vector<std::shared_ptr<Map>> maps;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".map") {
            try {
                auto map = loadMapFromFile(entry.path().string());
                maps.push_back(map);
            } catch (const std::exception& e) {
                Logger::error("[MapFileLoader] Failed to load map: " +
                              entry.path().filename().string() +
                              ". Error: " + e.what());
            }
        }
    }

    return maps;
}

/**
 * @brief Load a map from a file
 *
 * @param filePath The path to the map file
 * @return std::shared_ptr<Map> The loaded map
 */
std::shared_ptr<Map>
MapFileLoader::loadMapFromFile(const std::string& filePath) {
    FileReader reader(filePath);
    auto lines = reader.readAllLines();

    std::string name;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    bool parsingMap = false;
    int32_t y = 0;

    for (const auto& line : lines) {
        if (line.find(NAME_LABEL) == 0) {
            name = line.substr(NAME_OFFSET);
        } else if (line == MAP_LABEL) {
            parsingMap = true;
        } else if (parsingMap) {
            if (line == END_LABEL) {
                parsingMap = false;
                continue;
            }

            parseMapLine(line, y++, obstacles);
        }
    }

    if (name.empty()) {
        throw std::runtime_error("Map file is missing a name: " + filePath);
    }

    Logger::success("[MapFileLoader] Successfully loaded map: " + name +
                    " with " + std::to_string(obstacles.size()) +
                    " obstacles.");

    return std::make_shared<Map>(name, obstacles);
}

/**
 * @brief Parse a line of the map file
 *
 * @param line The line to parse
 * @param y The y position of the line
 * @param obstacles The vector to store the obstacles
 */
void MapFileLoader::parseMapLine(
    const std::string& line, int32_t y,
    std::vector<std::shared_ptr<Obstacle>>& obstacles) {
    int32_t blockY = y * BLOCK_SIZE;

    for (size_t x = 0; x < line.size(); x += BLOCK_OFFSET) {
        std::string blockCode = line.substr(x, BLOCK_OFFSET);

        if (ObstacleManager::get().isObstacleCodeValid(blockCode)) {
            int32_t blockX =
                static_cast<int32_t>(x / BLOCK_OFFSET) * BLOCK_SIZE;

            auto obstacle = std::make_shared<Obstacle>(
                ObstacleManager::get().getObstacleType(blockCode),
                Point(blockX, blockY));

            obstacles.push_back(obstacle);
            ObstacleManager::get().addObstacle(obstacle);
        }
    }
}
