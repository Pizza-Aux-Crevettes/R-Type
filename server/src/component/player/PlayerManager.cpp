/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

#include "component/player/PlayerManager.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"
#include "util/RandomSpawn.hpp"

/**
 * @brief Construct a new PlayerManager:: Player Manager object
 *
 */
PlayerManager& PlayerManager::get() {
    static PlayerManager instance;
    return instance;
}

/**
 * @brief Create a player
 *
 * @param name The name of the player
 * @return std::shared_ptr<Player> The player
 */
std::shared_ptr<Player> PlayerManager::createPlayer(const std::string& name) {
    Point spawnPos = RandomSpawn::generateRandomSpawnPosition();
    
    auto player =
        std::make_shared<Player>(name, Point(spawnPos.getX(), spawnPos.getY()));
    _players.push_back(player);
    return player;
}

/**
 * @brief Find a player by ID
 *
 * @param playerId The ID of the player
 * @return std::shared_ptr<Player> The player
 */
std::shared_ptr<Player> PlayerManager::findByID(int32_t playerId) const {
    auto it = std::find_if(_players.begin(), _players.end(),
                           [playerId](const std::shared_ptr<Player>& player) {
                               return player->getId() == playerId;
                           });
    if (it != _players.end()) {
        return *it;
    }

    Logger::warning("[PlayerManager] Player not found. Player ID: " +
                    std::to_string(playerId));
    return nullptr;
}

/**
 * @brief Remove a player
 *
 * @param playerId The ID of the player
 * @return true If the player was removed
 * @return false If the player was not removed
 */
bool PlayerManager::removePlayer(int32_t playerId) {
    auto it = std::remove_if(_players.begin(), _players.end(),
                             [playerId](const std::shared_ptr<Player>& player) {
                                 return player->getId() == playerId;
                             });

    if (it != _players.end()) {
        _players.erase(it, _players.end());
        MapProtocol::sendEntityDeleted(playerId);
        return true;
    }

    Logger::warning("[PlayerManager] Failed to remove player. Player ID: " +
                    std::to_string(playerId));
    return false;
}

/**
 * @brief Move the player
 *
 * @param playerId The ID of the player
 * @param offsetX The X offset
 * @param offsetY The Y offset
 */
void PlayerManager::movePlayer(int32_t playerId, double offsetX,
                               double offsetY) {
    auto player = findByID(playerId);
    if (!player) {
        Logger::warning("[PlayerManager] Player not found. Player ID: " +
                        std::to_string(playerId));
        return;
    }

    Point currentPos = player->getPosition();
    int32_t moveX = ObstacleManager::get().getMaxMoveDistance(
        currentPos.getX(), currentPos.getY(), offsetX, 0);
    int32_t moveY = ObstacleManager::get().getMaxMoveDistance(
        currentPos.getX(), currentPos.getY(), 0, offsetY);

    Point newPos(currentPos.getX() + moveX, currentPos.getY() + moveY);
    player->setPosition(newPos);
}

/**
 * @brief Get all players
 *
 * @return const std::vector<std::shared_ptr<Player>>&
 */
const std::vector<std::shared_ptr<Player>>& PlayerManager::getPlayers() const {
    return _players;
}
