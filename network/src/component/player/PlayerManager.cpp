/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"
#include <algorithm>
#include <ranges>
#include <memory>

PlayerManager& PlayerManager::get() {
    static PlayerManager instance;
    return instance;
}

PlayerManager::PlayerManager() = default;

PlayerManager::~PlayerManager() = default;

int32_t PlayerManager::getNextUserId() const {
    if (_players.empty()) {
        return 1;
    }

    return *std::ranges::max_element(_players | std::views::keys) + 1;
}

std::shared_ptr<Player> PlayerManager::createPlayer(const std::string& name) {
    const int32_t userId = getNextUserId();

    if (_players.contains(userId)) {
        Logger::warning("[PlayerManager] Player with userId " +
                        std::to_string(userId) + " already exists.");

        return nullptr;
    }

    auto player =
        std::make_shared<Player>(userId, name, Point(0, 0), Point(20, 10), 1.0);

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
