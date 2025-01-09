/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.cpp
*/

#include "component/player/PlayerManager.hpp"
#include "component/map/MapManager.hpp"
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
    int32_t playerId = getNextUserId();

    if (_players.find(playerId) != _players.end()) {
        Logger::warning("[PlayerManager] Failed to create player. Player ID " +
                        std::to_string(playerId) + " already exists.");
        return nullptr;
    }

    auto player = std::make_shared<Player>(playerId, name, Point(0, 0),
                                           Point(20, 10), 1.0);
    _players[playerId] = player;

    Logger::success("[PlayerManager] Player created:\n"
                    "  - Player ID: " +
                    std::to_string(playerId) +
                    "\n"
                    "  - Name: " +
                    name +
                    "\n"
                    "  - Initial Position: (0, 0)");

    return player;
}

std::shared_ptr<Player> PlayerManager::findPlayerById(int32_t playerId) const {
    auto it = _players.find(playerId);
    if (it != _players.end()) {
        return it->second;
    }

    Logger::warning("[PlayerManager] Player not found. Player ID: " +
                    std::to_string(playerId));
    return nullptr;
}

bool PlayerManager::removePlayer(int32_t playerId) {
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

void PlayerManager::movePlayer(int32_t playerId, int offsetX, int offsetY) {
    auto player = findPlayerById(playerId);

    if (!player) {
        Logger::warning("[PlayerManager] Player not found. Player ID: " +
                        std::to_string(playerId));
        return;
    }

    Point currentPos = player->getPosition();
    Point newPos(currentPos.getX() + offsetX, currentPos.getY() + offsetY);

    if (!Map::get().isVoidBlock(newPos)) {
        Logger::info("[PlayerManager] Player " + std::to_string(playerId) +
                     " cannot move to blocked position (" +
                     std::to_string(newPos.getX()) + ", " +
                     std::to_string(newPos.getY()) + ").");
        return;
    }

    player->setPosition(newPos);
    Logger::success("[PlayerManager] Player " + std::to_string(playerId) +
                    " moved to position (" + std::to_string(newPos.getX()) +
                    ", " + std::to_string(newPos.getY()) + ").");
}

const std::unordered_map<int32_t, std::shared_ptr<Player>>&
PlayerManager::getPlayers() const {
    return _players;
}
