/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

/**
 * @brief Send a viewport update to a client
 *
 * @param udpSocket The UDP socket to use
 * @param clientAddr The client's address
 * @param viewport The new viewport
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: VIEWPORT_UPDATE
 * Payload: viewport (int)
 */
void MapProtocol::sendViewportUpdate(const int udpSocket,
                                     const sockaddr_in& clientAddr,
                                     int viewport, SmartBuffer& smartBuffer) {
    // Construct the buffer
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE);
    smartBuffer << static_cast<int32_t>(viewport);

    // Send the viewport update
    UdpSocket::send(udpSocket, clientAddr, smartBuffer);

    Logger::success("[MapProtocol] Viewport update sent to client: " +
                    std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                    std::to_string(ntohs(clientAddr.sin_port)) +
                    ", Viewport: " + std::to_string(viewport));
}

/**
 * @brief Send an obstacles update to a client
 *
 * @param udpSocket The UDP socket to use
 * @param clientAddr The client's address
 * @param obstacles The obstacles to send
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: BLOCKS_UPDATE
 * Payload: x (int), y (int), type (int)
 */
void MapProtocol::sendObstaclesUpdate(const int udpSocket,
                                      const sockaddr_in& clientAddr,
                                      const std::vector<Obstacle>& obstacles,
                                      SmartBuffer& smartBuffer) {
    // Check if there are obstacles to send
    if (obstacles.empty()) {
        Logger::warning("[MapProtocol] No obstacles to send to client: " +
                        std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                        std::to_string(ntohs(clientAddr.sin_port)));
        return;
    }

    // Send each obstacle
    for (const auto& obstacle : obstacles) {
        // Construct the buffer
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::BLOCKS_UPDATE);
        smartBuffer << static_cast<int16_t>(obstacle._x);
        smartBuffer << static_cast<int16_t>(obstacle._y);
        smartBuffer << static_cast<int16_t>(obstacle._type);

        // Send the obstacle
        UdpSocket::send(udpSocket, clientAddr, smartBuffer);
    }

    Logger::success("[MapProtocol] Obstacle updates sent to client: " +
                    std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                    std::to_string(ntohs(clientAddr.sin_port)) +
                    ", Total obstacles: " + std::to_string(obstacles.size()));
}
