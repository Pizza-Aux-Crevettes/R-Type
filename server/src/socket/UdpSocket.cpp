/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "component/bullet/BulletManager.hpp"
#include "component/bullet/BulletProtocol.hpp"
#include "component/enemy/EnemyManager.hpp"
#include "component/enemy/EnemyProtocol.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "component/obstacle/ObstacleProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

/**
 * @brief Get the UdpSocket instance
 *
 * @return UdpSocket&
 */
UdpSocket& UdpSocket::get() {
    static UdpSocket instance;
    return instance;
}

/**
 * @brief Destroy the UdpSocket:: UdpSocket object
 *
 */
UdpSocket::~UdpSocket() {
    close();
}

/**
 * @brief Initialize the UDP socket
 *
 */
void UdpSocket::init() {
    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket.");
    }

    _udpAddr.sin_family = AF_INET;
    _udpAddr.sin_addr.s_addr = INADDR_ANY;
    _udpAddr.sin_port = htons(PORT);
    if (bind(_udpSocket, reinterpret_cast<sockaddr*>(&_udpAddr),
             sizeof(_udpAddr)) < SUCCESS) {
        throw std::runtime_error("Bind failed for UDP socket.");
    }

    Logger::socket("[UDP Socket] Successfully initialized.");
}

/**
 * @brief Run the UDP socket
 *
 */
void UdpSocket::run() {
    std::thread readThread([this]() { readLoop(); });
    std::thread updateThread([this]() { updateLoop(); });
    std::thread sendThread([this]() { sendLoop(); });

    readThread.detach();
    updateThread.detach();
    sendThread.detach();
}

/**
 * @brief Read loop for the UDP socket
 *
 */
void UdpSocket::readLoop() {
    SmartBuffer smartBuffer;

    while (true) {
        char buffer[DEFAULT_BYTES] = {};
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);

        const ssize_t bytesRead =
            recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                     reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (bytesRead > SUCCESS) {
            addClient(clientAddr);

            smartBuffer.reset();
            smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer),
                               bytesRead);

            Protocol::handleMessage(_udpSocket, smartBuffer);
        }
    }
}

/**
 * @brief Update loop for the UDP socket
 *
 */
void UdpSocket::updateLoop() {
    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        if (!PlayerManager::get().getPlayers().empty()) {
            ObstacleManager::get().updateObstacles();
            EnemyManager::get().updateEnemies();
            BulletManager::get().updateBullets();
        }

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            frameEnd - frameStart);
        int sleepTime = TICK_PER_SECOND - duration.count();

        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } else {
            Logger::warning(
                "[UDP Socket] Tick delay on update loop exceeded 50 ms! Took " +
                std::to_string(duration.count()) + " ms.");
        }
    }
}

/**
 * @brief Send loop for the UDP socket
 *
 */
void UdpSocket::sendLoop() {
    SmartBuffer smartBuffer;

    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        if (!PlayerManager::get().getPlayers().empty() &&
            !getClients().empty()) {
            for (const auto& client : _clients) {
                PlayerProtocol::sendPlayerPosition(client, smartBuffer);
                MapProtocol::sendViewportUpdate(client, smartBuffer);
                ObstacleProtocol::sendObstaclesUpdate(client, smartBuffer);
                EnemyProtocol::sendEnemiesUpdate(client, smartBuffer);
                BulletProtocol::sendBulletsUpdate(client, smartBuffer);
            }
        }

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd -
                                                                  frameStart);
        int sleepTime = TICK_PER_SECOND - frameDuration.count();

        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } else {
            Logger::warning("[UDP Socket] Tick delay on send loop exceeded " +
                            std::to_string(TICK_PER_SECOND) + " ms! Took " +
                            std::to_string(frameDuration.count()) + " ms.");
        }
    }
}

/**
 * @brief Send a message to a client
 *
 * @param clientSocket The UDP socket
 * @param smartBuffer The SmartBuffer to send
 */
void UdpSocket::sendToOne(const sockaddr_in& clientAddr,
                          const SmartBuffer& smartBuffer) {
    sendto(_udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
           reinterpret_cast<const sockaddr*>(&clientAddr), sizeof(clientAddr));
}

/**
 * @brief Send a message to all clients
 *
 * @param smartBuffer The SmartBuffer to send
 */
void UdpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    std::lock_guard lock(_clientsMutex);
    for (const auto& client : _clients) {
        sendto(_udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
               reinterpret_cast<const sockaddr*>(&client), sizeof(client));
    }
}

/**
 * @brief Send a message to all clients
 *
 * @param smartBuffer The SmartBuffer to send
 */
void UdpSocket::addClient(const sockaddr_in& clientAddr) {
    std::lock_guard lock(_clientsMutex);
    for (const auto& client : _clients) {
        if (client.sin_addr.s_addr == clientAddr.sin_addr.s_addr &&
            client.sin_port == clientAddr.sin_port) {
            return;
        }
    }

    _clients.push_back(clientAddr);

    Logger::socket("[UDP Socket] New client connected: " +
                   std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                   std::to_string(ntohs(clientAddr.sin_port)));
}

/**
 * @brief Get all clients
 *
 * @return std::vector<sockaddr_in>
 */
std::vector<sockaddr_in> UdpSocket::getClients() {
    std::lock_guard lock(_clientsMutex);
    return _clients;
}

/**
 * @brief Close the UDP socket
 *
 */
void UdpSocket::close() const {
    if (_udpSocket != FAILURE) {
        ::close(_udpSocket);

        Logger::socket("[UDP Socket] Closed.");
    }
}
