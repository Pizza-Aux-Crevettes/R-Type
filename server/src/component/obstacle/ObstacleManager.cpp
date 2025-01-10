/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ObstacleManager.cpp
*/

#include "component/obstacle/ObstacleManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Get the ObstacleManager instance
 *
 * @return ObstacleManager&
 */
ObstacleManager& ObstacleManager::get() {
    static ObstacleManager instance;
    return instance;
}

/**
 * @brief Construct a new ObstacleManager:: Obstacle Manager object
 *
 */
ObstacleManager::ObstacleManager() {
    // Initialize obstacle mappings
    _obstacleMapping = {
        {"0001", ObstacleType::BLOCK},
        {"0002", ObstacleType::BLOCK2},
        {"0003", ObstacleType::BLOCK3},
        {"0004", ObstacleType::BLOCK4},
    };

    Logger::info("[ObstacleManager] Initialized obstacle mappings.");
}

/**
 * @brief Add an obstacle
 *
 * @param obstacle The obstacle to add
 */
void ObstacleManager::addObstacle(const std::shared_ptr<Obstacle>& obstacle) {
    _obstacles.push_back(obstacle);

    Logger::success(
        "[ObstacleManager] Added obstacle. ID: " +
        std::to_string(obstacle->getId()) +
        ", Type: " + std::to_string(static_cast<int>(obstacle->getType())) +
        ", Position: (" + std::to_string(obstacle->getPosition().getX()) +
        ", " + std::to_string(obstacle->getPosition().getY()) + ")");
}

/**
 * @brief Get all obstacles
 *
 * @return std::vector<std::shared_ptr<Obstacle>> The obstacles
 */
std::vector<std::shared_ptr<Obstacle>> ObstacleManager::getObstacles() const {
    return _obstacles;
}

/**
 * @brief Check if an obstacle code is valid
 *
 * @param code The obstacle code
 * @return bool
 */
bool ObstacleManager::isObstacleCodeValid(const std::string& code) const {
    return _obstacleMapping.find(code) != _obstacleMapping.end();
}

/**
 * @brief Get the obstacle type by code
 *
 * @param code The obstacle code
 * @return ObstacleType The obstacle type
 */
ObstacleType ObstacleManager::getObstacleType(const std::string& code) const {
    auto it = _obstacleMapping.find(code);
    if (it != _obstacleMapping.end()) {
        return it->second;
    }

    throw std::runtime_error("[ObstacleManager] Invalid obstacle code: " +
                             code);
}

/**
 * @brief Reset the obstacle manager
 *
 */
void ObstacleManager::reset() {
    _obstacles.clear();

    Logger::info("[ObstacleManager] Cleared all obstacles.");
}
