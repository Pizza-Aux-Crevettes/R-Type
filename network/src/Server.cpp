/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

#include <stdexcept>
#include <iostream>
#include "Server.hpp"
#include "Logger.hpp"

Server::Server(Config port) : port(port), tcpSocket(port), udpSocket(port) {
    Logger::info("Starting server initialization...");

    tcpSocket.init();
    Logger::success("TCP socket initialized successfully.");

    udpSocket.init();
    Logger::success("UDP socket initialized successfully.");

    Logger::success("Server initialization complete.");
}

Server::~Server() {
    Logger::info("Shutting down server...");

    closeThreads();
    tcpSocket.close();
    udpSocket.close();

    Logger::success("Server shutdown complete.");
}

int Server::start() {
    Logger::info("Server started. Listening for connections...");

    try {
        std::thread udpThread(&UdpSocket::listen, &udpSocket);
        udpThread.detach();
        tcpSocket.listen();
    } catch (const std::exception &exception) {
        Logger::error("Runtime error: " + std::string(exception.what()));
        return ERROR;
    }

    return SUCCESS;
}

void Server::closeThreads() {
    for (auto &thread : clientThreads) {
        if (thread.joinable()) {
            thread.join();
            Logger::info("Client thread joined.");
        }
    }
}
