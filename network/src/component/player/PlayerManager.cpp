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
        Logger::info(
            "[PlayerManager] No players found. Starting with playerId 1.");
        return 1;
    }

    auto maxKeyIt = std::ranges::max_element(
        _players, {}, [](auto& pair) { return pair.first; });

    Logger::info("[PlayerManager] Next playerId will be: " +
                 std::to_string(maxKeyIt->first + 1));

    return maxKeyIt->first + 1;
}

std::shared_ptr<Player> PlayerManager::createPlayer(const std::string& name) {
    Logger::info("[PlayerManager] Attempting to create player with name: " +
                 name);

    int32_t playerId = getNextUserId();
    if (_players.find(playerId) != _players.end()) {
        Logger::warning("[PlayerManager] Player with playerId " +
                        std::to_string(playerId) + " already exists.");
        return nullptr;
    }

    auto player = std::make_shared<Player>(playerId, name, Point(0, 0),
                                           Point(20, 10), 1.0);
    _players[playerId] = player;

    Logger::success(
        "[PlayerManager] Successfully created player with playerId " +
        std::to_string(playerId) + ", name: " + name);

    return player;
}

std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t playerId) const {
    Logger::info("[PlayerManager] Searching for player with playerId: " +
                 std::to_string(playerId));

    auto it = _players.find(playerId);
    if (it != _players.end()) {
        Logger::info("[PlayerManager] Found player with playerId: " +
                     std::to_string(playerId));
        return it->second;
    }

    Logger::warning("[PlayerManager] Player with playerId " +
                    std::to_string(playerId) + " not found.");
    return nullptr;
}

bool PlayerManager::removePlayer(int32_t playerId) {
    Logger::info("[PlayerManager] Attempting to remove player with playerId: " +
                 std::to_string(playerId));

    auto it = _players.find(playerId);
    if (it != _players.end()) {
        _players.erase(it);

        Logger::success(
            "[PlayerManager] Successfully removed player with playerId " +
            std::to_string(playerId));
        return true;
    }

    Logger::warning("[PlayerManager] Failed to remove player with playerId " +
                    std::to_string(playerId));
    return false;
}

const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    Logger::info("[PlayerManager] Retrieving all players. Total count: " +
                 std::to_string(_players.size()));
    return _players;
}
