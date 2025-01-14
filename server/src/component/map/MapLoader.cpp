/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapLoader.cpp
*/

#include "component/map/MapLoader.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "util/Config.hpp"
#include "util/FileReader.hpp"
#include "util/Logger.hpp"

namespace fs = std::filesystem;

/**
 * @brief Load a map from a file
 *
 * @param filePath The path to the map file
 */
void MapLoader::loadMapFromFile(const std::string& filePath) {
    FileReader reader(filePath);
    auto lines = reader.readAllLines();

    std::string name;
    bool parsingMap = false;
    int32_t y = 0;

    ObstacleManager::get().reset();

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

            parseMapLine(line, y++);
        }
    }

    if (name.empty()) {
        throw std::runtime_error("[MapLoader] Map file missing name: " +
                                 filePath);
    }

    Logger::success("[MapLoader] Successfully loaded map: " + name);
}

/**
 * @brief Parse a line of the map file
 *
 * @param line The line to parse
 * @param y The y position of the line
 */
void MapLoader::parseMapLine(const std::string& line, int32_t y) {
    int32_t blockY = y * BLOCK_SIZE;

    for (size_t x = 0; x < line.size(); x += BLOCK_OFFSET) {
        std::string blockCode = line.substr(x, BLOCK_OFFSET);

        if (ObstacleManager::get().isObstacleCodeValid(blockCode)) {
            int32_t blockX =
                static_cast<int32_t>(x / BLOCK_OFFSET) * BLOCK_SIZE;

            auto obstacle = std::make_shared<Obstacle>(
                ObstacleManager::get().getObstacleType(blockCode),
                Point(blockX, blockY));

            ObstacleManager::get().addObstacle(obstacle);
        }
    }
}
