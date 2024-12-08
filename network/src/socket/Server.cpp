/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.cpp
*/

#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <iomanip>
#include <stdexcept>
#include <unistd.h>

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

Server::Server() : _tcpSocket(), _udpSocket(), _frequency(DEFAULT_FREQUENCY) {
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

void Server::setFrequency(int frequency) {
    _frequency = frequency;

    Logger::info("[Server] Frequency set to " + std::to_string(frequency) +
                 " Hz.");
}

int Server::getFrequency() const {
    return _frequency;
}

std::string Server::getDateTime() const {
    auto now = std::time(nullptr);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

std::string Server::getPwd() const {
    char buffer[256];

    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }

    return "Unknown";
}

double Server::getMemoryUsageMB() const {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    return usage.ru_maxrss / 1024.0;
}

double Server::getMemoryUsagePercent() const {
    return (getMemoryUsageMB() / 8192.0) * 100.0;
}

double Server::getCpuUsagePercent() const {
    static double lastCpuTime = 0;
    static auto lastTime = std::chrono::steady_clock::now();

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - lastTime;

    lastTime = now;
    lastCpuTime += 10.0;

    return lastCpuTime;
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
