/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

#include "component/player/PlayerManager.hpp"
#include "component/map/MapManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new PlayerManager:: PlayerManager object
 *
 */
PlayerManager& PlayerManager::get() {
    static PlayerManager instance;
    return instance;
}

/**
 * @brief Create a new player
 *
 * @param name The player's name
 * @return std::shared_ptr<Player> The created player
 */
std::shared_ptr<Player> PlayerManager::createPlayer(const std::string& name) {
    // Create the player
    auto player =
        std::make_shared<Player>(name, Point(50, 50), Point(20, 10), 1.0);
    _players[player->getId()] = player;

    Logger::success("[PlayerManager] Player created:\n"
                    "  - Player ID: " +
                    std::to_string(player->getId()) +
                    "\n"
                    "  - Name: " +
                    name +
                    "\n"
                    "  - Initial Position: X:" +
                    std::to_string(player->getPosition().getX()) +
                    ", Y:" + std::to_string(player->getPosition().getY()));

    return player;
}

/**
 * @brief Find a player by their ID
 *
 * @param playerId The player's ID
 * @return std::shared_ptr<Player> The player
 */
std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t playerId) const {
    // Find the player by their ID
    auto it = _players.find(playerId);
    if (it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player not found. Player ID: " +
                    std::to_string(playerId));
    return nullptr;
}

/**
 * @brief Remove a player by their ID
 *
 * @param playerId The player's ID
 * @return true If the player was removed
 * @return false If the player was not removed
 */
bool PlayerManager::removePlayer(int32_t playerId) {
    // Find the player by their ID
    auto it = _players.find(playerId);
    if (it != _players.end()) {
        _players.erase(it);

        Logger::success("[PlayerManager] Player removed. Player ID: " +
                        std::to_string(playerId));
        return true;
    }

    Logger::warning("[PlayerManager] Failed to remove player. Player ID: " +
                    std::to_string(playerId));
    return false;
}

/**
 * @brief Move a player by their ID
 *
 * @param playerId The player's ID
 * @param offsetX The X offset
 * @param offsetY The Y offset
 */
void PlayerManager::movePlayer(int32_t playerId, int32_t offsetX, int32_t offsetY) {
    // Find the player by their ID
    auto player = findPlayerById(playerId);
    if (!player) {
        Logger::warning("[PlayerManager] Player not found. Player ID: " +
                        std::to_string(playerId));
        return;
    }

    // Calculate the new position
    Point currentPos = player->getPosition();
    Point newPos(currentPos.getX() + offsetX, currentPos.getY() + offsetY);

    // Check if the new position is valid
    if (!MapManager::get().getCurrentMap()->isVoidBlock(newPos.getX(),
                                                        newPos.getY())) {
        Logger::info("[PlayerManager] Player " + std::to_string(playerId) +
                     " cannot move to blocked position (" +
                     std::to_string(newPos.getX()) + ", " +
                     std::to_string(newPos.getY()) + ").");
        return;
    }

    // Move the player if the position is valid
    player->setPosition(newPos);
    Logger::success("[PlayerManager] Player " + std::to_string(playerId) +
                    " moved to position (" + std::to_string(newPos.getX()) +
                    ", " + std::to_string(newPos.getY()) + ").");
}

/**
 * @brief Get the players
 *
 * @return const std::unordered_map<int32_t, std::shared_ptr<Player>>& The
 * players
 */
const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    return _players;
}
