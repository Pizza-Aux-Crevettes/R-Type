/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.cpp
*/

#include "component/room/Room.hpp"
#include "util/Logger.hpp"

Room::Room(int id, const std::string& code, size_t capacity)
    : _id(id), _code(code), _capacity(capacity) {
    Logger::info("[Room] Created room with ID: " + std::to_string(id) +
                 ", Code: " + code + ", Capacity: " + std::to_string(capacity));
}

int Room::getId() const {
    Logger::debug("[Room] Accessed ID: " + std::to_string(_id));

    return _id;
}

const std::string& Room::getCode() const {
    Logger::debug("[Room] Accessed Code: " + _code);

    return _code;
}

size_t Room::getCapacity() const {
    Logger::debug("[Room] Accessed Capacity: " + std::to_string(_capacity));

    return _capacity;
}

const std::vector<std::shared_ptr<Player>>& Room::getPlayers() const {
    Logger::debug("[Room] Accessed list of players in Room ID: " +
                  std::to_string(_id));

    return _players;
}

bool Room::addPlayer(const std::shared_ptr<Player>& player) {
    if (_players.size() >= _capacity) {
        Logger::warning("[Room] Cannot add player: " + player->getName() +
                        ". Room ID: " + std::to_string(_id) + " is full.");

        return false;
    }

    _players.push_back(player);

    Logger::info("[Room] Player " + player->getName() +
                 " added to Room ID: " + std::to_string(_id));

    return true;
}

bool Room::removePlayer(const std::string& playerName) {
    auto it =
        std::remove_if(_players.begin(), _players.end(),
                       [&playerName](const std::shared_ptr<Player>& player) {
                           return player->getName() == playerName;
                       });

    if (it != _players.end()) {
        _players.erase(it, _players.end());

        Logger::info("[Room] Player " + playerName +
                     " removed from Room ID: " + std::to_string(_id));

        return true;
    }

    Logger::warning("[Room] Player " + playerName +
                    " not found in Room ID: " + std::to_string(_id));

    return false;
}
