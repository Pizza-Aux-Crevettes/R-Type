/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Send a viewport update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: VIEWPORT_UPDATE
 * Payload: viewport (double)
 */
void MapProtocol::sendViewportUpdate(const sockaddr_in& clientAddr,
                                     SmartBuffer& smartBuffer) {
    double viewport = ObstacleManager::get().getViewport();

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::VIEWPORT_UPDATE)
                << static_cast<double>(viewport);

    UdpSocket::get().sendToOne(clientAddr, smartBuffer);

    Logger::packet("[MapProtocol] Viewport update sent to client Viewport: " +
                   std::to_string(viewport));
}

/**
 * @brief Send an obstacles update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: OBSTACLES_UPDATE
 * Payload: id (int32_t), x (int32_t), y (int32_t), type (int16_t)
 */
void MapProtocol::sendObstaclesUpdate(const sockaddr_in& clientAddr,
                                      SmartBuffer& smartBuffer) {
    const auto& visibleObstacles = ObstacleManager::get().getAllObstacles();
    for (const auto& obstacle : visibleObstacles) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::OBSTACLES_UPDATE)
                    << static_cast<int32_t>(obstacle->getId())
                    << static_cast<int32_t>(
                           obstacle->getPosition().getX() -
                           ObstacleManager::get().getViewport())
                    << static_cast<int32_t>(obstacle->getPosition().getY())
                    << static_cast<int16_t>(BLOCK_SIZE)
                    << static_cast<int16_t>(obstacle->getType());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);

        Logger::packet(
            "[MapProtocol] Obstacle update sent:\n"
            "  - ID: " +
            std::to_string(obstacle->getId()) + "\n  - Position: (" +
            std::to_string(obstacle->getPosition().getX()) + ", " +
            std::to_string(obstacle->getPosition().getY()) + ")" +
            "\n  - Type: " +
            ObstacleManager::get().ObstacleTypeToString(obstacle->getType()));
    }
}

/**
 * @brief Send a obstacle deleted to all clients
 *
 * @param obstacleId The block ID
 *
 * Protocol: OBSTACLES_DELETED
 * Payload: obstacleId (int32_t)
 */
void MapProtocol::sendObstaclesDeleted(const sockaddr_in& clientAddr,
                                       SmartBuffer& smartBuffer) {
    /*const auto& differences = ObstacleManager::get().getDifferences();
    for (const auto& obstacle : differences) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::OBSTACLE_DELETED)
                    << static_cast<int32_t>(obstacle->getId());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);

        Logger::packet("[MapProtocol] Obstacle deleted sent:\n"
                       "  - ID: " +
                       std::to_string(obstacle->getId()));
    }*/
}
