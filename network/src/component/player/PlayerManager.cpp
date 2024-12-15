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

PlayerManager& PlayerManager::getInstance() {
    static PlayerManager instance;
    return instance;
}

PlayerManager::PlayerManager() = default;

PlayerManager::~PlayerManager() = default;

std::shared_ptr<Player> PlayerManager::createPlayer(int32_t userId,
                                                    const std::string& name) {
    if (_players.contains(userId)) {
        Logger::warning("[PlayerManager] Player with userId " +
                        std::to_string(userId) + " already exists.");
        return nullptr;
    }

    auto player =
        std::make_shared<Player>(userId, name, Point(0, 0), Point(1, 1), 1.0);

    _players[userId] = player;

    Logger::success("[PlayerManager] Created player with userId " +
                    std::to_string(userId) + ", Name: " + name);

    return player;
}

std::shared_ptr<Player>
PlayerManager::findPlayerById(const int32_t userId) const {
    if (const auto it = _players.find(userId); it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player with userId " +
                    std::to_string(userId) + " not found.");

    return nullptr;
}

std::shared_ptr<Player>
PlayerManager::createPlayerByThread(const std::string& name) {
    std::lock_guard lock(_mutex);
    const auto threadId = std::this_thread::get_id();

    if (const auto it = _threadIds.find(threadId); it != _threadIds.end()) {
        return findPlayerById(it->second);
    }

    const int32_t newUserId = _nextuserId++;
    auto newPlayer = createPlayer(newUserId, name);
    newPlayer->setThreadId(threadId);

    _threadIds[threadId] = newUserId;

    Logger::info("[PlayerManager] Created player for thread " +
                 std::to_string(std::hash<std::thread::id>{}(threadId)) +
                 " with ID " + std::to_string(newUserId));

    return newPlayer;
}

bool PlayerManager::removePlayer(const int32_t userId) {
    if (const auto it = _players.find(userId); it != _players.end()) {
        _players.erase(it);

        Logger::success("[PlayerManager] Removed player with userId " +
                        std::to_string(userId));

        return true;
    }

    Logger::warning("[PlayerManager] Failed to remove player with userId " +
                    std::to_string(userId));

    return false;
}

const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    return _players;
}
