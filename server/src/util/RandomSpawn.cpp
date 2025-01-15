/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RandomSpawn.cpp
*/

#include "util/RandomSpawn.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Generate a random spawn position
 *
 * @return const Point The spawn position
 */
const Point RandomSpawn::generateRandomSpawnPosition() {
    const int xMin = BLOCK_SIZE + 20;
    const int xMax = 100;
    const int yMin = BLOCK_SIZE + 20;
    const int yMax = MAP_HEIGHT - BLOCK_SIZE - 20;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(xMin, xMax);
    std::uniform_int_distribution<> distY(yMin, yMax);

    const int maxAttempts = 100;

    for (int i = 0; i < maxAttempts; ++i) {
        int x = distX(gen);
        int y = distY(gen);

        if (RandomSpawn::isSpawnFree(x, y)) {
            return Point(x, y);
        }
    }

    Logger::warning("[PlayerManager] Failed to find a free spawn position "
                    "after 100 attempts. Fallback to (84, 84).");
    return Point(84, 84);
}

/**
 * @brief Check if a spawn position is free
 *
 * @param x The x position
 * @param y The y position
 * @return true If the spawn position is free
 * @return false If the spawn position is not free
 */
bool RandomSpawn::isSpawnFree(int x, int y) {
    const auto& obstacles = ObstacleManager::get().getAllObstacles();
    for (const auto& obs : obstacles) {
        if (obs->contains(x, y) || obs->contains(x + PLAYER_WIDTH, y) ||
            obs->contains(x, y + PLAYER_HEIGHT) ||
            obs->contains(x + PLAYER_WIDTH, y + PLAYER_HEIGHT)) {
            return false;
        }
    }

    const auto& players = PlayerManager::get().getPlayers();
    for (const auto& player : players) {
        int px = player->getPosition().getX();
        int py = player->getPosition().getY();

        bool overlapX = (x + PLAYER_WIDTH > px) && (x < px + PLAYER_WIDTH);
        bool overlapY = (y + PLAYER_HEIGHT > py) && (y < py + PLAYER_HEIGHT);
        if (overlapX && overlapY) {
            return false;
        }
    }

    return true;
}
