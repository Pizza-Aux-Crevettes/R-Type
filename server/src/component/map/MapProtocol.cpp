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

void MapProtocol::sendViewportUpdate(const int udpSocket,
                                     const sockaddr_in& clientAddr,
                                     int viewport, SmartBuffer& smartBuffer) {
    Logger::info("[MapProtocol] Sending viewport update. Viewport: " +
                 std::to_string(viewport) +
                 " to client: " + inet_ntoa(clientAddr.sin_addr) + ":" +
                 std::to_string(ntohs(clientAddr.sin_port)));

    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE)
                << static_cast<int32_t>(viewport);

    UdpSocket::send(udpSocket, clientAddr, smartBuffer);

    Logger::info("[MapProtocol] Viewport update sent successfully.");
}

void MapProtocol::sendObstaclesUpdate(const int udpSocket,
                                      const sockaddr_in& clientAddr,
                                      const std::vector<Obstacle>& obstacles,
                                      SmartBuffer& smartBuffer) {
    Logger::info("[MapProtocol] Sending obstacles update. Total obstacles: " +
                 std::to_string(obstacles.size()) +
                 " to client: " + inet_ntoa(clientAddr.sin_addr) + ":" +
                 std::to_string(ntohs(clientAddr.sin_port)));

    for (const auto& obstacle : obstacles) {
        smartBuffer.reset();

        smartBuffer << static_cast<int16_t>(Protocol::OpCode::BLOCKS_UPDATE)
                    << static_cast<int16_t>(obstacle._x)
                    << static_cast<int16_t>(obstacle._y)
                    << static_cast<int16_t>(obstacle._type);

        UdpSocket::send(udpSocket, clientAddr, smartBuffer);

        Logger::info(
            "[MapProtocol] Obstacle update sent. Position: (" +
            std::to_string(obstacle._x) + ", " + std::to_string(obstacle._y) +
            "), Type: " + std::to_string(static_cast<int>(obstacle._type)));
    }

    Logger::info("[MapProtocol] All obstacles updates sent successfully.");
}