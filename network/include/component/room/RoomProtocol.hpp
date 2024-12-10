/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.hpp
*/

/**
 * @file RoomProtocol.hpp
 * @brief Declaration of the RoomProtocol class for handling room-related
 * operations.
 */

#pragma once

#include <SmartBuffer.hpp>
#include <string>

/**
 * @class RoomProtocol
 * @brief Handles room-related operations such as creating, joining, and
 * deleting rooms.
 *
 * The RoomProtocol class provides static methods for processing room management
 * requests from clients. These operations include creating new rooms, joining
 * existing rooms, and deleting rooms.
 */
class RoomProtocol {
  public:
    /**
     * @brief Handles the CREATE_ROOM operation.
     *
     * Processes a client's request to create a new room. The function extracts
     * relevant data from the SmartBuffer, validates it, and creates a room if
     * conditions are met. The response is sent back to the client.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the request data.
     */
    static void createRoom(int clientSocket, SmartBuffer& smartBuffer);

    /**
     * @brief Handles the JOIN_ROOM operation.
     *
     * Processes a client's request to join an existing room. The function
     * extracts relevant data from the SmartBuffer, validates the player's
     * eligibility, and adds the player to the room if conditions are met. The
     * response is sent back to the client.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the request data.
     */
    static void joinRoom(int clientSocket, SmartBuffer& smartBuffer);

    /**
     * @brief Handles the DELETE_ROOM operation.
     *
     * Processes a client's request to delete an existing room. The function
     * extracts relevant data from the SmartBuffer, validates the requester's
     * permissions, and deletes the room if conditions are met. The response is
     * sent back to the client.
     *
     * @param clientSocket The socket associated with the client.
     * @param smartBuffer The buffer containing the request data.
     */
    static void deleteRoom(int clientSocket, SmartBuffer& smartBuffer);
};
