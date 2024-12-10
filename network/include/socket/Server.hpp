/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

/**
 * @file Server.hpp
 * @brief Declaration of the Server class for managing the application's server
 * operations.
 */

#pragma once

#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include <thread>
#include <vector>

/**
 * @class Server
 * @brief Singleton class responsible for managing server-side operations.
 *
 * The Server class handles initialization, starting the main server loop,
 * managing TCP and UDP sockets, and cleaning up resources during shutdown.
 */
class Server {
  public:
    /**
     * @brief Retrieves the singleton instance of the Server.
     *
     * @return Server& Reference to the Server instance.
     */
    static Server& getInstance();

    /**
     * @brief Starts the server and begins handling connections.
     *
     * Initializes the TCP and UDP listeners and manages incoming connections.
     *
     * @return int Status code: 0 for success, non-zero for errors.
     */
    int start();

  private:
    /**
     * @brief Constructs the Server instance.
     *
     * Initializes the TCP and UDP sockets and prepares the server for
     * operations.
     *
     * @throws std::runtime_error if socket initialization fails.
     */
    Server();

    /**
     * @brief Destructs the Server instance.
     *
     * Ensures all resources, including sockets and threads, are properly
     * released.
     */
    ~Server();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Server(const Server&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    Server& operator=(const Server&) = delete;

    TcpSocket _tcpSocket; /**< The TCP socket for handling TCP connections. */
    UdpSocket
        _udpSocket; /**< The UDP socket for handling UDP communications. */
    std::vector<std::thread> _clientThreads; /**< A collection of threads for
                                                handling client operations. */

    /**
     * @brief Closes all client threads gracefully.
     *
     * Ensures that all client threads are joined and resources are cleaned up.
     */
    void closeThreads();
};
