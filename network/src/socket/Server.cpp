/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <stdexcept>

Server& Server::get() {
    static Server instance;
    return instance;
}

Server::Server() {
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
        throw std::runtime_error(std::string(e.what()));
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
        _threads.emplace_back(&UdpSocket::readLoop, &_udpSocket);
        Logger::thread("[Server] UDP read loop thread started.");

        _threads.emplace_back(&UdpSocket::sendLoop, &_udpSocket);
        Logger::thread("[Server] UDP send loop thread started.");

        _threads.emplace_back(&TcpSocket::readLoop, &_tcpSocket);
        Logger::thread("[Server] TCP read loop thread started.");

        while (true)
            std::this_thread::sleep_for(
                std::chrono::seconds(1)); // DON'T BE EEPY
    } catch (const std::exception& exception) {
        Logger::error("[Server] Runtime error: " +
                      std::string(exception.what()));

        return ERROR;
    }
}

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
