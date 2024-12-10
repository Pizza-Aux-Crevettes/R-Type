/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.cpp
*/

/**
 * @file Singletons.cpp
 * @brief Provides global access to singleton instances used in the application.
 *
 * This file defines utility functions to retrieve singleton instances
 * for various core components like Server, RoomManager, PlayerManager,
 * Protocol, ...
 */

#include "util/Singletons.hpp"

/**
 * @brief Retrieves the singleton instance of the server.
 *
 * This function provides access to the server instance, which manages
 * TCP/UDP connections and handles communication between clients and the game
 * logic.
 *
 * @return Server& A reference to the singleton server instance.
 */
Server& Singletons::getServer() {
    return Server::getInstance();
}

/**
 * @brief Retrieves the singleton instance of the RoomManager.
 *
 * The RoomManager is responsible for managing game rooms, including creating,
 * joining, and deleting rooms.
 *
 * @return RoomManager& A reference to the singleton RoomManager instance.
 */
RoomManager& Singletons::getRoomManager() {
    return RoomManager::getInstance();
}

/**
 * @brief Retrieves the singleton instance of the PlayerManager.
 *
 * The PlayerManager handles player-related operations, such as creating,
 * retrieving, and managing player data.
 *
 * @return PlayerManager& A reference to the singleton PlayerManager instance.
 */
PlayerManager& Singletons::getPlayerManager() {
    return PlayerManager::getInstance();
}

/**
 * @brief Retrieves the singleton instance of the Protocol.
 *
 * The Protocol handles message parsing and execution of commands based on
 * predefined operation codes (OpCodes) received from clients.
 *
 * @return Protocol& A reference to the singleton Protocol instance.
 */
Protocol& Singletons::getProtocol() {
    return Protocol::getInstance();
}
