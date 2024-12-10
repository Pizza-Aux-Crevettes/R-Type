/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.hpp
*/

/**
 * @file Singletons.hpp
 * @brief Provides centralized access to singleton instances of core components
 * like the server, player manager, and room manager.
 */

#pragma once

#include "component/player/PlayerManager.hpp"
#include "component/room/RoomManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"

/**
 * @class Singletons
 * @brief Utility class to manage and provide access to singleton instances.
 *
 * This class provides static methods to retrieve instances of key components
 * in the application, ensuring centralized and thread-safe access.
 */
class Singletons {
  public:
    /**
     * @brief Retrieves the singleton instance of the Server.
     *
     * @return Reference to the Server instance.
     */
    static Server& getServer();

    /**
     * @brief Retrieves the singleton instance of the RoomManager.
     *
     * @return Reference to the RoomManager instance.
     */
    static RoomManager& getRoomManager();

    /**
     * @brief Retrieves the singleton instance of the PlayerManager.
     *
     * @return Reference to the PlayerManager instance.
     */
    static PlayerManager& getPlayerManager();

    /**
     * @brief Retrieves the singleton instance of the Protocol.
     *
     * @return Reference to the Protocol instance.
     */
    static Protocol& getProtocol();

  private:
    /**
     * @brief Private default constructor to prevent instantiation.
     */
    Singletons() = default;

    /**
     * @brief Private destructor to prevent deletion.
     */
    ~Singletons() = default;

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Singletons(const Singletons&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    Singletons& operator=(const Singletons&) = delete;
};
