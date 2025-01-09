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
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: MAP_VIEWPORT_UPDATE
 * Payload: viewport (int)
 */
void MapProtocol::sendViewportUpdate(const int udpSocket,
                                     const sockaddr_in& clientAddr,
                                     SmartBuffer& smartBuffer) {
    // Get the viewport for the map
    const auto& viewport = MapManager::get().getCurrentMap()->getViewport();

    // Construct the buffer
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::MAP_VIEWPORT_UPDATE);
    smartBuffer << static_cast<int32_t>(viewport);

    // Send the viewport update
    UdpSocket::send(udpSocket, clientAddr, smartBuffer);

    Logger::packet("[MapProtocol] Viewport update sent to client: " +
                   std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                   std::to_string(ntohs(clientAddr.sin_port)) +
                   ", Viewport: " + std::to_string(viewport));
}

/**
 * @brief Send an obstacles update to a client
 *
 * @param udpSocket The UDP socket to use
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: MAP_OBSTACLES_UPDATE
 * Payload: x (int), y (int), type (int)
 */
void MapProtocol::sendObstaclesUpdate(const int udpSocket,
                                      const sockaddr_in& clientAddr,
                                      SmartBuffer& smartBuffer) {
    // Get the obstacles for the map
    const auto& obstacles =
        MapManager::get().getCurrentMap()->getObstaclesByViewport();

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
        smartBuffer << static_cast<int16_t>(
            Protocol::OpCode::MAP_OBSTACLES_UPDATE);
        smartBuffer << static_cast<int16_t>(obstacle._x);
        smartBuffer << static_cast<int16_t>(obstacle._y);
        smartBuffer << static_cast<int16_t>(obstacle._type);

        // Send the obstacle
        UdpSocket::send(udpSocket, clientAddr, smartBuffer);

        // Sleep for a short time to avoid packet loss
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Logger::packet("[MapProtocol] Obstacle updates sent to client: " +
                   std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                   std::to_string(ntohs(clientAddr.sin_port)) +
                   ", Total obstacles: " + std::to_string(obstacles.size()));
}
