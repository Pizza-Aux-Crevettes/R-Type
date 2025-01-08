/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.cpp
*/

#include "component/room/Room.hpp"
#include "util/Logger.hpp"

Room::Room(const std::string& code, const std::shared_ptr<Player>& owner,
           const size_t capacity, const bool isPublic)
    : _code(code), _owner(owner), _capacity(capacity), _isPublic(isPublic) {}

void Room::startGame() {
    _gameStarted = true;
}

void Room::stopGame() {
    _gameStarted = false;
}

bool Room::isGameStarted() const {
    return _gameStarted;
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
        return false;
    }

    _players.push_back(player);

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

        return true;
    }

    return false;
}
