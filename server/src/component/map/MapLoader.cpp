/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapLoader.cpp
*/

#include "component/map/MapLoader.hpp"
#include "component/enemy/EnemyManager.hpp"
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
    int32_t blockY = y * OBSTACLE_SIZE;

    for (size_t x = 0; x < line.size(); x += OBSTACLE_OFFSET) {
        std::string code = line.substr(x, OBSTACLE_OFFSET);

        if (ObstacleManager::get().isObstacleCodeValid(code)) {
            int32_t blockX =
                static_cast<int32_t>(x / OBSTACLE_OFFSET) * OBSTACLE_SIZE;

            auto obstacle = std::make_shared<Obstacle>(
                ObstacleManager::get().getObstacleType(code),
                Point(blockX, blockY));
            ObstacleManager::get().addObstacle(obstacle);
        } else if (EnemyManager::get().isEnemyCodeValid(code)) {
            int32_t enemyX =
                static_cast<int32_t>(x / OBSTACLE_OFFSET) * OBSTACLE_SIZE;

            const auto& properties =
                EnemyManager::get().getEnemyProperties(code);

            auto enemy = std::make_shared<Enemy>(
                properties.type, Point(enemyX, blockY), properties.speed,
                properties.width, properties.height, properties.bulletSpeed,
                properties.bulletDamage, properties.shootCooldown,
                properties.shootRange, properties.health);

            EnemyManager::get().addEnemy(enemy);
        }
    }
}
