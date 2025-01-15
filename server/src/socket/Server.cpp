/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

#include "socket/Server.hpp"
#include <stdexcept>
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Get the Server instance
 *
 * @return Server&
 */
Server& Server::get() {
    static Server instance;
    return instance;
}

/**
 * @brief Construct a new Server:: Server object
 *
 */
Server::Server() {
    Logger::info("[Server] Starting initialization...");

    try {
        _tcpSocket.init();
        _udpSocket.init();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string(e.what()));
    }
}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server() {
    Logger::info("[Server] Shutting down...");

    closeThreads();
    _tcpSocket.close();
    _udpSocket.close();

    Logger::success("[Server] Shutdown complete.");
}

int Server::start() {
    Logger::info("[Server] Starting main loop. Listening for connections...");

    try {
        _threads.emplace_back([&]() { _udpSocket.run(); });
        _threads.emplace_back(&TcpSocket::readLoop, &_tcpSocket);

        while (true)
            std::this_thread::sleep_for(
                std::chrono::seconds(1)); // DON'T BE EEPY
    } catch (const std::exception& exception) {
        Logger::error("[Server] Runtime error: " +
                      std::string(exception.what()));

        return ERROR;
    }
}

/**
 * @brief Close all threads
 *
 */
void Server::closeThreads() {
    Logger::info("[Server] Closing threads...");

    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    _threads.clear();

    Logger::info("[Server] All threads closed.");
}
