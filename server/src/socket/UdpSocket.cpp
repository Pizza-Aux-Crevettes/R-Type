/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new UdpSocket:: UdpSocket object
 *
 */
UdpSocket::UdpSocket() : _udpSocket(FAILURE) {}

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
    // Create the socket
    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket.");
    }

    // Bind the socket
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
 * @brief Read loop for the UDP socket
 *
 */
void UdpSocket::readLoop() {
    SmartBuffer smartBuffer;

    while (true) {
        char buffer[DEFAULT_BYTES] = {};
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);

        // Read the message
        const ssize_t bytesRead =
            recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                     reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (bytesRead > SUCCESS) {
            // Add the client to the list
            addClient(clientAddr);

            // Handle the message
            smartBuffer.reset();
            smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer),
                               bytesRead);
            Protocol::handleMessage(_udpSocket, smartBuffer, clientAddr);
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
        // Get all clients and players
        const auto clients = getClients();
        const auto& players = PlayerManager::get().getPlayers();
        if (clients.empty() || players.empty()) {
            return;
        }

        // Real-time updates to all clients
        for (const sockaddr_in& client : clients) {
            // Send the player updates
            for (const auto& [playerId, player] : players) {
                PlayerProtocol::sendPositionsUpdate(_udpSocket, client, player,
                                                    smartBuffer);
            }

            // Send the map updates
            MapProtocol::sendViewportUpdate(_udpSocket, client, smartBuffer);
            MapProtocol::sendObstaclesUpdate(_udpSocket, client, smartBuffer);
        }

        // Increment the viewport
        MapManager::get().getCurrentMap()->incrementViewport();

        // Sleep for a short time
        std::this_thread::sleep_for(std::chrono::milliseconds(FREQUENCY));
    }
}

/**
 * @brief Send a message to a client
 *
 * @param udpSocket The UDP socket
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to send
 */
void UdpSocket::sendToOne(const int udpSocket, const sockaddr_in& clientAddr,
                          const SmartBuffer& smartBuffer) {
    sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
           reinterpret_cast<const sockaddr*>(&clientAddr), sizeof(clientAddr));
}

/**
 * @brief Handle a read message
 *
 * @param smartBuffer The SmartBuffer to handle
 */
void UdpSocket::addClient(const sockaddr_in& clientAddr) {
    std::lock_guard lock(_clientsMutex);

    // Check if the client is already registered
    for (const auto& client : _clients) {
        if (client.sin_addr.s_addr == clientAddr.sin_addr.s_addr &&
            client.sin_port == clientAddr.sin_port) {
            return;
        }
    }

    // Register the client
    _clients.push_back(clientAddr);

    Logger::info("[UDP Socket] New client registered: " +
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
