/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ObstacleManager.cpp
*/

#include "component/obstacle/ObstacleManager.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Config.hpp"
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
    _obstacleMapping = {
        {"0001", ObstacleType::BLOCK},
        {"0002", ObstacleType::BLOCK2},
        {"0003", ObstacleType::BLOCK3},
        {"0004", ObstacleType::BLOCK4},
    };

    Logger::success("[ObstacleManager] Initialized obstacle mappings.");
}

ObstacleManager::~ObstacleManager() {
    _obstacles.clear();
    _visibleObstacles.clear();
}

/**
 * @brief Convert an ObstacleType to a string
 *
 * @param type The ObstacleType
 * @return std::string The string representation
 */
std::string ObstacleManager::ObstacleTypeToString(ObstacleType type) {
    switch (type) {
    case ObstacleType::NONE:
        return "NONE";
    case ObstacleType::BLOCK:
        return "BLOCK";
    case ObstacleType::BLOCK2:
        return "BLOCK2";
    case ObstacleType::BLOCK3:
        return "BLOCK3";
    case ObstacleType::BLOCK4:
        return "BLOCK4";
    default:
        return "UNKNOWN";
    }
}

/**
 * @brief Add an obstacle
 *
 * @param obstacle The obstacle to add
 */
void ObstacleManager::addObstacle(const std::shared_ptr<Obstacle>& obstacle) {
    _obstacles.push_back(obstacle);
}

/**
 * @brief Get all obstacles
 *
 * @return const std::vector<std::shared_ptr<Obstacle>>& The obstacles
 */
const std::vector<std::shared_ptr<Obstacle>>&
ObstacleManager::getAllObstacles() const {
    return _obstacles;
}

/**
 * @brief Get the visible obstacles
 *
 * @return const std::vector<std::shared_ptr<Obstacle>>& The visible obstacles
 */
const std::vector<std::shared_ptr<Obstacle>>&
ObstacleManager::getVisibleObstacles() const {
    return _visibleObstacles;
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
 * @brief Update the viewport and visible obstacles
 *
 */
void ObstacleManager::updateObstacles() {
    _visibleObstacles.clear();
    _viewport += MAP_SPEED;

    auto players = PlayerManager::get().getPlayers();

    for (const auto& obstacle : _obstacles) {
        obstacle->setPosition(Point(obstacle->getPosition().getX() - MAP_SPEED,
                                    obstacle->getPosition().getY()));

        for (const auto& [id, player] : players) {
            if (obstacle->collidesWith(player)) {
                PlayerManager::get().movePlayer(player->getId(), -MAP_SPEED, 0);
            }
        }

        if (obstacle->getPosition().getX() < RENDER_DISTANCE * BLOCK_SIZE &&
            obstacle->getPosition().getX() > -BLOCK_SIZE) {
            _visibleObstacles.push_back(obstacle);
        }
        if (obstacle->getPosition().getX() < -BLOCK_SIZE) {
            MapProtocol::sendEntityDeleted(obstacle->getId());
        }
    }
}

/**
 * @brief Check if the player can move to a specific position
 *
 * @param x The x coordinate of the new position
 * @param y The y coordinate of the new position
 * @return int32_t The maximum distance the player can move before collision
 */
int32_t ObstacleManager::getMaxMoveDistance(int32_t x, int32_t y,
                                            int32_t offsetX,
                                            int32_t offsetY) const {
    for (const auto& obstacle : _obstacles) {
        int32_t blockX = obstacle->getPosition().getX();
        int32_t blockY = obstacle->getPosition().getY();

        if (offsetX != 0) {
            if (y + PLAYER_HEIGHT > blockY && y < blockY + BLOCK_SIZE) {
                if (offsetX > 0 && x + PLAYER_WIDTH <= blockX &&
                    x + PLAYER_WIDTH + offsetX > blockX) {
                    return blockX - (x + PLAYER_WIDTH);
                } else if (offsetX < 0 && x >= blockX + BLOCK_SIZE &&
                           x + offsetX < blockX + BLOCK_SIZE) {
                    return blockX + BLOCK_SIZE - x;
                }
            }
        }

        if (offsetY != 0) {
            if (x + PLAYER_WIDTH > blockX && x < blockX + BLOCK_SIZE) {
                if (offsetY > 0 && y + PLAYER_HEIGHT <= blockY &&
                    y + PLAYER_HEIGHT + offsetY > blockY) {
                    return blockY - (y + PLAYER_HEIGHT);
                } else if (offsetY < 0 && y >= blockY + BLOCK_SIZE &&
                           y + offsetY < blockY + BLOCK_SIZE) {
                    return blockY + BLOCK_SIZE - y;
                }
            }
        }
    }

    if (offsetX != 0) {
        if (x + offsetX < 0) {
            return -x;
        } else if (x + PLAYER_WIDTH + offsetX > MAP_WIDTH) {
            return MAP_WIDTH - (x + PLAYER_WIDTH);
        }
    }

    if (offsetY != 0) {
        if (y + offsetY < 0) {
            return -y;
        } else if (y + PLAYER_HEIGHT + offsetY > MAP_HEIGHT) {
            return MAP_HEIGHT - (y + PLAYER_HEIGHT);
        }
    }

    return offsetX != 0 ? offsetX : offsetY;
}

/**
 * @brief Get the viewport
 *
 * @return double The viewport
 */
double ObstacleManager::getViewport() const {
    return _viewport;
}
