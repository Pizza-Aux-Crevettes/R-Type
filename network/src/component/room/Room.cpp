/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.cpp
*/

#include "component/room/Room.hpp"
#include <algorithm>
#include <memory>
#include "util/Logger.hpp"

Room::Room(const std::string& code, const std::shared_ptr<Player>& owner,
           const size_t capacity, const bool isPublic)
    : _code(code), _owner(owner), _capacity(capacity), _isPublic(isPublic) {
    Logger::info("[Room] Created room with Code: " + code +
                 ", Capacity: " + std::to_string(capacity) +
                 ", Public: " + (isPublic ? "true" : "false"));
}

void Room::setMap(const std::shared_ptr<Map>& map) {
    _map = map;
}

std::shared_ptr<Map> Room::getMap() const {
    return _map;
}

const std::string& Room::getCode() const {
    return _code;
}

const std::shared_ptr<Player>& Room::getOwner() const {
    return _owner;
}

size_t Room::getCapacity() const {
    return _capacity;
}

bool Room::isPublic() const {
    return _isPublic;
}

const std::vector<std::shared_ptr<Player>>& Room::getPlayers() const {
    return _players;
}

bool Room::addPlayer(const std::shared_ptr<Player>& player) {
    if (_players.size() >= _capacity) {
        Logger::warning("[Room] Cannot add player: " + player->getName() +
                        ". Room Code: " + _code + " is full.");

        return false;
    }
    _players.push_back(player);

    Logger::info("[Room] Player " + player->getName() +
                 " added to Room Code: " + _code);

    return true;
}

bool Room::removePlayer(const std::string& playerName) {
    const auto it = std::ranges::remove_if(
                        _players,
                        [&playerName](const std::shared_ptr<Player>& player) {
                            return player->getName() == playerName;
                        })
                        .begin();

    if (it != _players.end()) {
        _players.erase(it, _players.end());

        Logger::info("[Room] Player " + playerName +
                     " removed from Room Code: " + _code);

        return true;
    }

    Logger::warning("[Room] Player " + playerName +
                    " not found in Room Code: " + _code);

    return false;
}
