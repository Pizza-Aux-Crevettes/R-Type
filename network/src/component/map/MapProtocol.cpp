/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"

void MapProtocol::sendViewportUpdate(int clientSocket, int viewport) {
    SmartBuffer smartBuffer;
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE);
    smartBuffer << static_cast<int32_t>(viewport);

    TcpSocket::sendToOne(clientSocket, smartBuffer);
}

void MapProtocol::sendObstaclesUpdate(int clientSocket,
                                      const std::vector<Obstacle>& obstacles) {
    SmartBuffer smartBuffer;

    for (const auto& obstacle : obstacles) {
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::BLOCKS_UPDATE);
        smartBuffer << static_cast<int16_t>(obstacle._x)
                    << static_cast<int16_t>(obstacle._y)
                    << static_cast<int16_t>(obstacle._type);
        TcpSocket::sendToOne(clientSocket, smartBuffer);
    }
}
