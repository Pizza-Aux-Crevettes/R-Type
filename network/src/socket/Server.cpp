/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

/**
 * @file Server.cpp
 * @brief Implementation of the Server class, managing TCP and UDP sockets.
 */

#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <iomanip>
#include <stdexcept>

/**
 * @brief Retrieves the singleton instance of the Server.
 * @return The singleton instance of the Server.
 */
Server& Server::getInstance() {
    static Server instance;
    return instance;
}

/**
 * @brief Constructs the Server, initializing TCP and UDP sockets.
 * @throws std::runtime_error If initialization fails for TCP or UDP sockets.
 */
Server::Server() : _tcpSocket(), _udpSocket() {
    Logger::info("[Server] Starting initialization...");

    try {
        _tcpSocket.init();

        Logger::socket("[Server] TCP socket initialized successfully on port " +
                       std::to_string(PORT) + ".");

        _udpSocket.init();

        Logger::socket("[Server] UDP socket initialized successfully on port " +
                       std::to_string(PORT) + ".");

        Logger::success("[Server] Initialization complete.");
    } catch (const std::exception& e) {
        Logger::error("[Server] Initialization failed: " +
                      std::string(e.what()));

        throw;
    }
}

/**
 * @brief Destructs the Server, ensuring resources are released.
 */
Server::~Server() {
    Logger::info("[Server] Shutting down...");

    closeThreads();

    _tcpSocket.close();
    _udpSocket.close();

    Logger::success("[Server] Shutdown complete.");
}

/**
 * @brief Starts the server, launching listeners for TCP and UDP connections.
 * @return SUCCESS (0) on successful execution, ERROR (-1) otherwise.
 */
int Server::start() {
    Logger::info("[Server] Starting main loop. Listening for connections...");

    try {
        // Start UDP listener in a separate thread.
        std::thread udpThread(&UdpSocket::listen, &_udpSocket);
        udpThread.detach();

        Logger::thread("[Server] UDP listener thread started.");

        // Start TCP listener in the main thread.
        _tcpSocket.listen();
    } catch (const std::exception& exception) {
        Logger::error("[Server] Runtime error: " +
                      std::string(exception.what()));

        return ERROR;
    }

    return SUCCESS;
}

/**
 * @brief Closes all active client threads gracefully.
 */
void Server::closeThreads() {
    Logger::info("[Server] Closing client threads...");

    for (auto& thread : _clientThreads) {
        if (thread.joinable()) {
            thread.join();

            Logger::thread("[Server] Client thread joined successfully.");
        } else {
            Logger::warning(
                "[Server] Attempted to join a non-joinable thread.");
        }
    }

    Logger::info("[Server] All client threads closed.");
}
