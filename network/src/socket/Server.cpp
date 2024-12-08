/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

#include "socket/Server.hpp"
#include "util/Logger.hpp"
#include <iostream>
#include <stdexcept>

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
        std::thread udpThread(&UdpSocket::listen, &_udpSocket);
        udpThread.detach();

        Logger::thread("[Server] UDP listener thread started.");

        _tcpSocket.listen();
    } catch (const std::exception& exception) {
        Logger::error("[Server] Runtime error: " +
                      std::string(exception.what()));

        return ERROR;
    }

    return SUCCESS;
}

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
