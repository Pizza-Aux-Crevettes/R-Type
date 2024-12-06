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

Protocol Server::protocol;

Protocol& Server::getProtocol() {
    return protocol;
}

Server::Server(Config port) : port(port), tcpSocket(port), udpSocket(port) {
    Logger::info("[Server] Starting initialization...");

    try {
        tcpSocket.init();
        Logger::socket("[Server] TCP socket initialized successfully on port " +
                       std::to_string(port) + ".");

        udpSocket.init();
        Logger::socket("[Server] UDP socket initialized successfully on port " +
                       std::to_string(port) + ".");

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

    tcpSocket.close();
    udpSocket.close();

    Logger::success("[Server] Shutdown complete.");
}

int Server::start() {
    Logger::info("[Server] Starting main loop. Listening for connections...");

    try {
        std::thread udpThread(&UdpSocket::listen, &udpSocket);
        udpThread.detach();
        Logger::thread("[Server] UDP listener thread started.");

        tcpSocket.listen();
    } catch (const std::exception& exception) {
        Logger::error("[Server] Runtime error: " +
                      std::string(exception.what()));
        return ERROR;
    }

    return SUCCESS;
}

void Server::closeThreads() {
    Logger::info("[Server] Closing client threads...");

    for (auto& thread : clientThreads) {
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
