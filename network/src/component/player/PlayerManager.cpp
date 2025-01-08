/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"

PlayerManager& PlayerManager::get() {
    static PlayerManager instance;
    return instance;
}

int32_t PlayerManager::getNextUserId() const {
    if (_players.empty()) {
        return 1;
    }

    auto maxKeyIt = std::ranges::max_element(
        _players, {}, [](auto& pair) { return pair.first; });

    return maxKeyIt->first + 1;
}

std::shared_ptr<Player> PlayerManager::createPlayer(const std::string& name) {
    int32_t userId = getNextUserId();

    if (_players.find(userId) != _players.end()) {
        Logger::warning("[PlayerManager] Player with userId " +
                        std::to_string(userId) + " already exists.");
        return nullptr;
    }

    auto player =
        std::make_shared<Player>(userId, name, Point(0, 0), Point(20, 10), 1.0);

    _players[userId] = player;

    Logger::success("[PlayerManager] Created player with userId " +
                    std::to_string(userId) + ", name: " + name);
    return player;
}

std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t userId) const {
    auto it = _players.find(userId);
    if (it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player with userId " +
                    std::to_string(userId) + " not found.");
    return nullptr;
}

bool PlayerManager::removePlayer(int32_t userId) {
    auto it = _players.find(userId);

    if (it != _players.end()) {
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