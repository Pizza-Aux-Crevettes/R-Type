/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.cpp
*/

/**
 * @file Room.cpp
 * @brief Implements the logic for managing rooms, including adding and removing
 * players.
 */

#include "component/room/Room.hpp"
#include "util/Logger.hpp"

/**
 * @brief Constructs a new Room object.
 *
 * @param code Unique code of the room.
 * @param owner The player who owns the room.
 * @param capacity The maximum number of players the room can hold.
 * @param isPublic Whether the room is publicly visible.
 */
Room::Room(const std::string& code, const std::shared_ptr<Player>& owner,
           size_t capacity, bool isPublic)
    : _code(code), _owner(owner), _capacity(capacity), _isPublic(isPublic) {
    Logger::info("[Room] Created room with Code: " + code +
                 ", Capacity: " + std::to_string(capacity) +
                 ", Public: " + (isPublic ? "true" : "false"));
}

/**
 * @brief Gets the unique code of the room.
 *
 * @return const std::string& The unique room code.
 */
const std::string& Room::getCode() const {
    return _code;
}

/**
 * @brief Gets the owner of the room.
 *
 * @return const std::shared_ptr<Player>& The owner of the room.
 */
const std::shared_ptr<Player>& Room::getOwner() const {
    return _owner;
}

/**
 * @brief Gets the maximum capacity of the room.
 *
 * @return size_t The maximum number of players the room can hold.
 */
size_t Room::getCapacity() const {
    return _capacity;
}

/**
 * @brief Checks if the room is public.
 *
 * @return bool True if the room is public, false otherwise.
 */
bool Room::isPublic() const {
    return _isPublic;
}

/**
 * @brief Gets the list of players currently in the room.
 *
 * @return const std::vector<std::shared_ptr<Player>>& The players in the room.
 */
const std::vector<std::shared_ptr<Player>>& Room::getPlayers() const {
    return _players;
}

/**
 * @brief Adds a player to the room.
 *
 * @param player The player to add.
 * @return bool True if the player was successfully added, false if the room is
 * full.
 */
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

/**
 * @brief Removes a player from the room by their name.
 *
 * @param playerName The name of the player to remove.
 * @return bool True if the player was successfully removed, false otherwise.
 */
bool Room::removePlayer(const std::string& playerName) {
    auto it =
        std::remove_if(_players.begin(), _players.end(),
                       [&playerName](const std::shared_ptr<Player>& player) {
                           return player->getName() == playerName;
                       });

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
