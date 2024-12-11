/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.hpp
*/

/**
 * @file Room.hpp
 * @brief Declaration of the Room class for managing game rooms.
 */

#pragma once

#include "component/player/Player.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @class Room
 * @brief Represents a room in the game where players can interact.
 *
 * The Room class manages the players within it, its owner, and other attributes
 * such as its capacity and whether it is public or private.
 */
class Room {
  public:
    /**
     * @brief Constructs a new Room instance.
     *
     * @param code The unique code identifying the room.
     * @param owner The player who owns the room.
     * @param capacity The maximum number of players allowed in the room.
     * @param isPublic Indicates whether the room is public or private.
     */
    Room(const std::string& code, const std::shared_ptr<Player>& owner,
         size_t capacity, bool isPublic);

    /**
     * @brief Retrieves the unique code of the room.
     *
     * @return A constant reference to the room's unique code.
     */
    const std::string& getCode() const;

    /**
     * @brief Retrieves the owner of the room.
     *
     * @return A shared pointer to the player who owns the room.
     */
    const std::shared_ptr<Player>& getOwner() const;

    /**
     * @brief Retrieves the capacity of the room.
     *
     * @return The maximum number of players allowed in the room.
     */
    size_t getCapacity() const;

    /**
     * @brief Checks whether the room is public.
     *
     * @return True if the room is public, false if it is private.
     */
    bool isPublic() const;

    /**
     * @brief Retrieves the list of players currently in the room.
     *
     * @return A constant reference to a vector of shared pointers to players.
     */
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;

    /**
     * @brief Adds a player to the room.
     *
     * Checks if there is enough capacity in the room before adding the player.
     *
     * @param player The player to add to the room.
     * @return True if the player was successfully added, false if the room is
     * full.
     */
    bool addPlayer(const std::shared_ptr<Player>& player);

    /**
     * @brief Removes a player from the room by name.
     *
     * @param playerName The name of the player to remove.
     * @return True if the player was successfully removed, false if the player
     * was not found.
     */
    bool removePlayer(const std::string& playerName);

  private:
    std::string _code;              ///< The unique code identifying the room.
    std::shared_ptr<Player> _owner; ///< The owner of the room.
    size_t _capacity; ///< The maximum number of players allowed in the room.
    bool _isPublic;   ///< Indicates whether the room is public or private.
    std::vector<std::shared_ptr<Player>>
        _players; ///< List of players in the room.
};
