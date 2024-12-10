/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.hpp
*/

/**
 * @file PlayerProtocol.hpp
 * @brief Declaration of the PlayerProtocol class for handling player-related
 * protocols.
 */

#pragma once

#include "protocol/Protocol.hpp"
#include "util/SmartBuffer.hpp"

/**
 * @class PlayerProtocol
 * @brief Handles the protocol logic for player-related actions.
 *
 * The PlayerProtocol class provides static methods to manage player
 * interactions, such as creating or retrieving a player when a new connection
 * is established.
 */
class PlayerProtocol {
  public:
    /**
     * @brief Handles the NEW_PLAYER protocol operation.
     *
     * Assigns a new player ID to the client or retrieves the existing player
     * associated with the current thread if already created.
     *
     * @param clientSocket The client socket through which the request was
     * received.
     * @param smartBuffer A reference to the SmartBuffer containing the protocol
     * data.
     */
    static void newPlayer(int clientSocket, SmartBuffer& smartBuffer);
};
