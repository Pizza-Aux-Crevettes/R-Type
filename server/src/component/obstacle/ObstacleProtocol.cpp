/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/obstacle/ObstacleProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"

/**
 * @brief Send an obstacles update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: UPDATE_OBSTACLES
 * Payload: id (int32_t), x (int32_t), y (int32_t), size (int16_t), type
 * (int16_t)
 */
void ObstacleProtocol::sendObstaclesUpdate(const sockaddr_in& clientAddr,
                                           SmartBuffer& smartBuffer) {
    const auto& visibleObstacles = ObstacleManager::get().getVisibleObstacles();
    for (const auto& obstacle : visibleObstacles) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::UPDATE_OBSTACLES)
                    << static_cast<int32_t>(obstacle->getId())
                    << static_cast<int32_t>(obstacle->getPosition().getX())
                    << static_cast<int32_t>(obstacle->getPosition().getY())
                    << static_cast<int16_t>(OBSTACLE_SIZE)
                    << static_cast<int16_t>(obstacle->getType());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);
    }
}
