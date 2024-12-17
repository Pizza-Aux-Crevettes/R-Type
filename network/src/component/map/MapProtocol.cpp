/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "MapProtocol.hpp"
#include "TcpSocket.hpp"
#include "protocol/Protocol.hpp"

void MapProtocol::sendViewportUpdate(int clientSocket, int viewport) {
    SmartBuffer smartBuffer;
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE);
    smartBuffer << static_cast<int32_t>(viewport);

    TcpSocket::sendToOne(clientSocket, smartBuffer);
}

void MapProtocol::sendBlocksUpdate(int clientSocket, const std::vector<Obstacle>& blocks) {
    SmartBuffer smartBuffer;

    for (const auto& block : blocks) {
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::BLOCKS_UPDATE);
        smartBuffer << static_cast<int16_t>(block.getX())
                    << static_cast<int16_t>(block.getY())
                    << static_cast<int16_t>(block.getWidth())
                    << static_cast<int16_t>(block.getHeight())
                    << static_cast<int16_t>(block.getType())
                    << static_cast<int16_t>(block.isTraversable());
        TcpSocket::sendToOne(clientSocket, smartBuffer);
    }
}
