/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Send a viewport update to a client
 *
 * @param udpSocket The UDP socket to use
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: VIEWPORT_UPDATE
 * Payload: viewport (int32_t)
 */
void MapProtocol::sendViewportUpdate(const sockaddr_in& clientAddr,
                                     SmartBuffer& smartBuffer) {
    const auto& viewport = MapManager::get().getCurrentMap()->getViewport();

    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE)
                << static_cast<int32_t>(viewport);

    UdpSocket::get().sendToOne(clientAddr, smartBuffer);

    Logger::packet("[MapProtocol] Viewport update sent to client.");
}

/**
 * @brief Send an obstacles update to a client
 *
 * @param udpSocket The UDP socket to use
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: OBSTACLES_UPDATE
 * Payload: id (int32_t), x (int32_t), y (int32_t), type (int16_t)
 */
void MapProtocol::sendObstaclesUpdate(const sockaddr_in& clientAddr,
                                      SmartBuffer& smartBuffer) {
    const auto& obstacles =
        MapManager::get().getCurrentMap()->getObstaclesByViewport();
    if (obstacles.empty()) {
        Logger::warning("[MapProtocol] No obstacles to send.");
        return;
    }

    for (const auto& obstacle : obstacles) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::OBSTACLES_UPDATE)
                    << static_cast<int32_t>(obstacle->getId())
                    << static_cast<int32_t>(obstacle->getPosition().getX())
                    << static_cast<int32_t>(obstacle->getPosition().getY())
                    << static_cast<int16_t>(BLOCK_SIZE)
                    << static_cast<int16_t>(obstacle->getType());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);
    }

    Logger::packet("[MapProtocol] Obstacles update sent to client.");
}
