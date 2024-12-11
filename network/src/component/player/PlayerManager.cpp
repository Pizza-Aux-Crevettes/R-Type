/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

/**
 * @file PlayerManager.cpp
 * @brief Manages the lifecycle and association of players with threads or IDs.
 */

#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"
#include <functional> // ==> std::hash

/**
 * @brief Returns the singleton instance of the PlayerManager.
 * @return PlayerManager& The singleton instance.
 */
PlayerManager& PlayerManager::getInstance() {
    static PlayerManager instance;
    return instance;
}

/**
 * @brief Constructs the RoomManager. Currently does nothing.
 */
PlayerManager::PlayerManager() : _nextPlayerId(1) {}

/**
 * @brief Destructs the PlayerManager. Currently does nothing.
 */
PlayerManager::~PlayerManager() {}

/**
 * @brief Creates a new player with the given ID and name.
 *
 * @param playerId The ID of the player to create.
 * @param name The name of the player.
 * @return A shared pointer to the newly created player, or nullptr if the
 * player already exists.
 */
std::shared_ptr<Player> PlayerManager::createPlayer(int32_t playerId,
                                                    const std::string& name) {
    if (_players.find(playerId) != _players.end()) {
        Logger::warning("[PlayerManager] Player with playerId " +
                        std::to_string(playerId) + " already exists.");
        return nullptr;
    }

    auto player =
        std::make_shared<Player>(playerId, name, Point(0, 0), Point(1, 1), 1.0);

    _players[playerId] = player;

    Logger::success("[PlayerManager] Created player with playerId " +
                    std::to_string(playerId) + ", Name: " + name);

    return player;
}

/**
 * @brief Finds a player by their unique ID.
 *
 * @param playerId The ID of the player to find.
 * @return A shared pointer to the player, or nullptr if not found.
 */
std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t playerId) const {
    auto it = _players.find(playerId);

    if (it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player with playerId " +
                    std::to_string(playerId) + " not found.");

    return nullptr;
}

/**
 * @brief Finds or creates a player for the current thread.
 *        Ensures each thread has a unique associated player.
 *
 * @param name The name to assign to the player if a new one is created.
 * @return A shared pointer to the player associated with the current thread.
 */
std::shared_ptr<Player>
PlayerManager::createPlayerByThread(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto threadId = std::this_thread::get_id();
    auto it = _threadIds.find(threadId);

    if (it != _threadIds.end()) {
        return findPlayerById(it->second);
    }

    int32_t newPlayerId = _nextPlayerId++;
    auto newPlayer = createPlayer(newPlayerId, name);
    newPlayer->setThreadId(threadId);

    _threadIds[threadId] = newPlayerId;

    Logger::info("[PlayerManager] Created player for thread " +
                 std::to_string(std::hash<std::thread::id>{}(threadId)) +
                 " with ID " + std::to_string(newPlayerId));

    return newPlayer;
}

/**
 * @brief Removes a player with the given ID from the manager.
 *
 * @param playerId The ID of the player to remove.
 * @return True if the player was successfully removed, false otherwise.
 */
bool PlayerManager::removePlayer(int32_t playerId) {
    auto it = _players.find(playerId);

    if (it != _players.end()) {
        _players.erase(it);

        Logger::success("[PlayerManager] Removed player with playerId " +
                        std::to_string(playerId));

        return true;
    }

    Logger::warning("[PlayerManager] Failed to remove player with playerId " +
                    std::to_string(playerId));

    return false;
}

/**
 * @brief Retrieves all players currently managed.
 *
 * @return A constant reference to the map of players.
 */
const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    return _players;
}
