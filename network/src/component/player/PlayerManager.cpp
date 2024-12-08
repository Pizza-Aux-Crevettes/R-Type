#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"

PlayerManager& PlayerManager::getInstance() {
    static PlayerManager instance;
    return instance;
}

PlayerManager::PlayerManager() {}

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
