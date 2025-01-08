/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"

void MapProtocol::sendViewportUpdate(const int udpSocket,
                                     const sockaddr_in& clientAddr,
                                     int viewport, SmartBuffer& smartBuffer) {
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE)
                << static_cast<int32_t>(viewport);

    UdpSocket::send(udpSocket, clientAddr, smartBuffer);
}

void MapProtocol::sendObstaclesUpdate(const int udpSocket,
                                      const sockaddr_in& clientAddr,
                                      const std::vector<Obstacle>& obstacles,
                                      SmartBuffer& smartBuffer) {
    for (const auto& obstacle : obstacles) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::BLOCKS_UPDATE)
                    << obstacle._x << obstacle._y << obstacle._type;

        UdpSocket::send(udpSocket, clientAddr, smartBuffer);
    }
}