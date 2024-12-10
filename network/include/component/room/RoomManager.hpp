/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomManager.hpp
*/

/**
 * @file RoomManager.hpp
 * @brief Declaration of the RoomManager class for managing rooms in the game.
 */

#pragma once

#include "component/room/Room.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @class RoomManager
 * @brief Manages the lifecycle and operations of rooms within the game.
 *
 * The RoomManager class provides functionalities to create, delete, and
 * retrieve rooms. It ensures that room codes are unique and manages room
 * ownership.
 */
class RoomManager {
  public:
    /**
     * @brief Retrieves the singleton instance of the RoomManager.
     *
     * @return The singleton instance of the RoomManager.
     */
    static RoomManager& getInstance();

    /**
     * @brief Creates a new room.
     *
     * Generates a unique room code and creates a new room with the specified
     * parameters.
     *
     * @param owner The player who owns the room.
     * @param capacity The maximum number of players allowed in the room.
     * @param isPublic Indicates whether the room is public or private.
     * @return A shared pointer to the newly created room.
     */
    std::shared_ptr<Room> createRoom(const std::shared_ptr<Player>& owner,
                                     size_t capacity, bool isPublic);

    /**
     * @brief Deletes an existing room.
     *
     * Deletes a room based on its code, provided the requester is the owner of
     * the room.
     *
     * @param roomCode The unique code of the room to be deleted.
     * @param requester The player requesting the deletion.
     * @return True if the room was successfully deleted, false otherwise.
     */
    bool deleteRoom(const std::string& roomCode,
                    const std::shared_ptr<Player>& requester);

    /**
     * @brief Finds a room by its code.
     *
     * Searches for a room with the specified unique code.
     *
     * @param code The unique code of the room.
     * @return A shared pointer to the room if found, nullptr otherwise.
     */
    std::shared_ptr<Room> findRoomByCode(const std::string& code) const;

    /**
     * @brief Retrieves all rooms.
     *
     * Provides access to the list of all currently active rooms.
     *
     * @return A constant reference to the vector of shared pointers to rooms.
     */
    const std::vector<std::shared_ptr<Room>>& getRooms() const;

  private:
    /**
     * @brief Constructs the RoomManager.
     *
     * The constructor is private to enforce the singleton pattern.
     */
    RoomManager();

    /**
     * @brief Destructs the RoomManager.
     */
    ~RoomManager();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    RoomManager(const RoomManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    RoomManager& operator=(const RoomManager&) = delete;

    /**
     * @brief Generates a unique code for a room.
     *
     * Ensures the generated code does not conflict with any existing room
     * codes.
     *
     * @return A unique room code as a string.
     */
    std::string generateUniqueCode() const;

    std::vector<std::shared_ptr<Room>> _rooms; ///< List of all active rooms.
};
