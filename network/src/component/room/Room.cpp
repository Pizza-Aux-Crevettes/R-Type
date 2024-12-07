/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.cpp
*/

#include "component/room/Room.hpp"

Room::Room(int id, const std::string& code, size_t capacity)
    : _id(id), _code(code), _capacity(capacity) {}

int Room::getId() const {
    return _id;
}

const std::string& Room::getCode() const {
    return _code;
}

size_t Room::getCapacity() const {
    return _capacity;
}

const std::vector<std::shared_ptr<Player>>& Room::getPlayers() const {
    return _players;
}

bool Room::addPlayer(const std::shared_ptr<Player>& player) {
    if (_players.size() >= _capacity) {
        return false;
    }

    _players.push_back(player);

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
        return true;
    }

    return false;
}
