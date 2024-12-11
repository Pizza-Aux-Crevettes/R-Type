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

PlayerManager& PlayerManager::getInstance() {
    static PlayerManager instance;
    return instance;
}

PlayerManager::PlayerManager() : _nextPlayerId(1) {}

PlayerManager::~PlayerManager() {}

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

std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t playerId) const {
    auto it = _players.find(playerId);

    if (it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player with playerId " +
                    std::to_string(playerId) + " not found.");

    return nullptr;
}

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

const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    return _players;
}
